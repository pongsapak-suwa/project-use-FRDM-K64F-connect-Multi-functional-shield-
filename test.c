#include "MK64F12.h"
void delayMs(int n);
int time = 0;
int main (void){
	SIM->SCGC5 |= (1 << SIM_SCGC5_PORTB_SHIFT) |  (1<< SIM_SCGC5_PORTD_SHIFT )| (1<< SIM_SCGC5_PORTA_SHIFT );
	PORTB -> PCR[3] = 0x100 ;
	PORTB -> PCR[10] = 0x100 ;
	PORTB -> PCR[11] = 0x100 ;
	PORTD -> PCR[0] = 0x100 ;
	PORTD -> PCR[1] = 0x100 ;
	PORTD -> PCR[2] = 0x100 ;
	PORTD -> PCR[3] = 0x100 ;
	PORTA -> PCR[1] = 0x100 ;
	
	PTB -> PDDR &= ~0xC08;
	PTD -> PDDR |= 0x0F;
	__disable_irq(); 
	PORTB->PCR[3] &= ~0xF0000; 
	PORTB->PCR[3] |= 0xA0000; 
	PORTB->PCR[10] &= ~0xF0000; 
	PORTB->PCR[10] |= 0xA0000; 
	PORTB->PCR[11] &= ~0xF0000; 
	PORTB->PCR[11] |= 0xA0000; 
	NVIC->ISER[1] |= 0x10000000; 
	__enable_irq();
	PTD -> PDOR |= 0x0F;

	while(1){
		if (time == 400){
			delayMs(time-300);
			time = time -100;
		}
		else if (time == 300){
			PTD -> PDOR |= 0x02;
			delayMs(time-200);
			time = time -100;
		}
		else if (time == 200){
			PTD -> PDOR |= 0x08;
			delayMs(time-100);
			time = time -100;
		}
		else if (time == 100){
			PTD -> PDOR |= 0x04;
			delayMs(time);
			time = time -100;
		}
		else if (time == 0){

			PTA -> PDDR &= ~0x02;
			PTD -> PDOR |= 0x01;
		}

	}
}
void PORTB_IRQHandler(void) {
	if ((PTB -> PDIR & 0x08)==0){
			PTD -> PDOR |= 0x0F;
			PTD -> PDOR &= ~0x0F;
			PTA -> PDDR = 0x02;
			time = 400;
			PORTB->ISFR = 0x008;
		}
	if ((PTB -> PDIR & 0x400)==0){
			PTD -> PDOR |= 0x0F;
			PTD -> PDOR &= ~0x0D;
			PTA -> PDDR = 0x02;
			time = 300;
			PORTB->ISFR = 0x400;
		}
	if ((PTB -> PDIR & 0x800)==0){
			PTD -> PDOR |= 0x0F;
			PTD -> PDOR &= ~0x05;
			PTA -> PDDR = 0x02;
			time = 200;
			PORTB->ISFR = 0x800;
		}
}

void delayMs(int n) {
	int i;
	SysTick->LOAD = 204800 - 1;

	
	SysTick->CTRL = 5; 
	for (i = 0; i < n; i++)
	while((SysTick->CTRL & 0x10000) == 0) { 
	}
	SysTick->CTRL = 0; 

}