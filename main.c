#include "MK64F12.h"
void delayMs(int n);
int time = 0;
int q;
int zero[8] = {1,1,0,0,0,0,0,0};
int numsegment[5][8] = {{0,1,0,0,0,0,0,0},{0,1,1,1,1,0,0,1},{0,0,1,0,0,1,0,0},{0,0,1,1,0,0,0,0},{0,0,0,1,1,0,0,1}}; // dp,g,f,e,d,c,b,a and 0,1,2,3,4 (value)
int seenum[4][8] = {{0,0,0,0,1,0,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,0,1}}; //position ----,000-,00-0,0-00,-000
void segment(int time);
int main (void){
	SIM->SCGC5 |= (1 << SIM_SCGC5_PORTB_SHIFT) |  (1<< SIM_SCGC5_PORTD_SHIFT )| (1<< SIM_SCGC5_PORTA_SHIFT ) | (1<< SIM_SCGC5_PORTC_SHIFT ); 
	//set GPIO
	//switch
	PORTB -> PCR[3] = 0x100 ;  //S1
	PORTB -> PCR[10] = 0x100 ; //S2
	PORTB -> PCR[11] = 0x100 ; //S3
	//led
	PORTD -> PCR[0] = 0x100 ; //D4
	PORTD -> PCR[1] = 0x100 ; //D1
	PORTD -> PCR[2] = 0x100 ; //D3
	PORTD -> PCR[3] = 0x100 ; //D2
	//buzzer
	PORTA -> PCR[1] = 0x100 ; 
	// 7 segment
	PORTB -> PCR[23] = 0x100 ; //LCHCLK
	PORTC -> PCR[3] = 0x100 ; //SFTCLK
	PORTC -> PCR[12] = 0x100 ; //SDI
	//output 7 segment
	PTC -> PDDR |= 0x01008;
	PTB -> PDDR |= 0x0800000;
	//input sw
	PTB -> PDDR &= ~0xC08;
	//output led
	PTD -> PDDR |= 0x0F;
	
	//sys timmer
	SysTick->LOAD = 204800 - 1; //1 ms
	SysTick->CTRL = 5; // enable counter, - no interrupt,- use system clock  bit0-2
	//FTM Timmer
	SIM->SCGC6 |= 0x01000000;  //enable clock gate to FTM0 bit24 set FTM1-25 FTM2-26 (selection)
#include "MK64F12.h"
void delayMs(int n);
int time = 0;
int q;
int zero[8] = {1,1,0,0,0,0,0,0};
int numsegment[5][8] = {{0,1,0,0,0,0,0,0},{0,1,1,1,1,0,0,1},{0,0,1,0,0,1,0,0},{0,0,1,1,0,0,0,0},{0,0,0,1,1,0,0,1}}; // dp,g,f,e,d,c,b,a and 0,1,2,3,4 (value)
int seenum[4][8] = {{0,0,0,0,1,0,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,0,1}}; //position ----,000-,00-0,0-00,-000
void segment(int time);
int main (void){
	SIM->SCGC5 |= (1 << SIM_SCGC5_PORTB_SHIFT) |  (1<< SIM_SCGC5_PORTD_SHIFT )| (1<< SIM_SCGC5_PORTA_SHIFT ) | (1<< SIM_SCGC5_PORTC_SHIFT ); 
	//set GPIO
	//switch
	PORTB -> PCR[3] = 0x100 ;  //S1
	PORTB -> PCR[10] = 0x100 ; //S2
	PORTB -> PCR[11] = 0x100 ; //S3
	//led
	PORTD -> PCR[0] = 0x100 ; //D4
	PORTD -> PCR[1] = 0x100 ; //D1
	PORTD -> PCR[2] = 0x100 ; //D3
	PORTD -> PCR[3] = 0x100 ; //D2
	//buzzer
	PORTA -> PCR[1] = 0x100 ; 
	// 7 segment
	PORTB -> PCR[23] = 0x100 ; //LCHCLK
	PORTC -> PCR[3] = 0x100 ; //SFTCLK
	PORTC -> PCR[12] = 0x100 ; //SDI
	//output 7 segment
	PTC -> PDDR |= 0x01008;
	PTB -> PDDR |= 0x0800000;
	//input sw
	PTB -> PDDR &= ~0xC08;
	//output led
	PTD -> PDDR |= 0x0F;
	
	//sys timmer
	SysTick->LOAD = 204800 - 1; //1 ms
	SysTick->CTRL = 5; // enable counter, - no interrupt,- use system clock  bit0-2
	//FTM Timmer
	SIM->SCGC6 |= 0x01000000;  //enable clock gate to FTM0 bit24 set FTM1-25 FTM2-26 (selection)
	SIM->SOPT2 |= 0 ; // enable MCGFLLCLK clock bit16-17
	FTM0->CNTIN = 0x00; //start 0
	FTM0->MOD = 0xFFFF; //end 65536 time = 3.2 ms
	FTM0->SC = 0x08; // bit 3 system clock
	
	PTC -> PDOR |= 0x01008;
	PTB -> PDOR |= 0x0800000;

	//interup switch
	__disable_irq(); //disable all irq
	PORTB->PCR[3] &= ~0xF0000; // clear interupt section bit16-19 set 0000
	PORTB->PCR[3] |= 0xA0000;  // enable falling edge bit16-19 set 1010
	PORTB->PCR[10] &= ~0xF0000; 
	PORTB->PCR[10] |= 0xA0000; 
	PORTB->PCR[11] &= ~0xF0000; 	
	PORTB->PCR[11] |= 0xA0000; 
	NVIC->ISER[1] |= 0x10000000; //enable NVIC-portB 60 mod 32 = bit28
	__enable_irq();  //enable all irq
	//set all led = 1
	PTD -> PDOR |= 0x0F;
	
	
	while(1){
				if (time == 4){
					PTA->PDOR = (SysTick->VAL)>>16;   // buzzer in systick
					segment(time);
					delayMs(1);
					time = time -1;          //time - 1
				}
				else if (time == 3){
					PTD -> PDOR |= 0x02;
					PTA->PDOR = (SysTick->VAL)>>14;
					segment(time);
					delayMs(1);
					time = time -1;
				}
				else if (time == 2){
					PTD -> PDOR |= 0x08;
					PTA->PDOR = (SysTick->VAL)>>12;
					segment(time);
					delayMs(1);
					time = time -1;
				}
				else if (time == 1){
					PTD -> PDOR |= 0x04;
					PTA->PDOR = (SysTick->VAL)>>10;
					segment(time);
					delayMs(1);
					PTA->PDOR = (SysTick->VAL)>>8;
					time = time - 1;
				}
				else if(time <= 0){
				PTA -> PDDR &= ~0x02;
				PTD -> PDOR |= 0x0F;
					
				segment(time);
				}
	}

	}
void PORTB_IRQHandler(void) {
	if ((PTB -> PDIR & 0x08)==0){   //press S1 
			PTD -> PDOR |= 0x0F;   //close all led
			PTD -> PDOR &= ~0x0F;  //led = 4
			PTA -> PDDR = 0x02;    
			time = 4;
			PORTB->ISFR = 0x008; //clear ISF portB pin3
		}
	if ((PTB -> PDIR & 0x400)==0){ //press S2
			PTD -> PDOR |= 0x0F;   //close all led
			PTD -> PDOR &= ~0x0D;  //led = 3
			PTA -> PDDR = 0x02;
			time = 3;
			PORTB->ISFR = 0x400; //clear ISF portB pin10
		}
	if ((PTB -> PDIR & 0x800)==0){ //press S3
			PTD -> PDOR |= 0x0F;  //close all led
			PTD -> PDOR &= ~0x05; //led = 2
			PTA -> PDDR = 0x02; 
			time = 2;
			PORTB->ISFR = 0x800; //clear ISF portB pin11
		}
}

void delayMs(int n) {
	int i;
	for(i = 0; i < (320*n); i++) { //320 = 1 sec
	while((FTM0->SC & 0x80) == 0) { //FTM0->sc = 1 if CNTIN = Mod,TOF=1
		segment(time);
	}
	FTM0->SC &= ~(0x80); //clear TOF 

	}
}

void segment(int time){
	for (int i= 0 ; i < 4;i++){     
		PTB -> PCOR = 0x0800000; //LCHCLK = 0
		if(i != 3){
			for (q= 0 ; q < 8;q++){                          //bit data
				PTC -> PDOR = (zero[q]) << 12; //SDI
				PTC -> PSOR = 0x08; //SFTCLK
				PTC -> PCOR = 0x08;
			}
		}else{
			for (q= 0 ; q < 8;q++){                          //bit data
				PTC -> PDOR = (numsegment[time][q]) << 12; //SDI
				PTC -> PSOR = 0x08; //SFTCLK
				PTC -> PCOR = 0x08;
			}
		}
			for (q = 0; q < 8; q++){                        //bit position
				PTC -> PDOR = (seenum[i][q]) << 12; //SDI
				PTC -> PSOR = 0x08; //SFTCLK
				PTC -> PCOR = 0x08;
			}
			PTB -> PSOR = 0x0800000;  //LCHCLK = 1
		}

}


