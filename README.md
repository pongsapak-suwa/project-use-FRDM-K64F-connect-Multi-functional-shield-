# project-use-FRDM-K64F-connect-Multi-functional-shield
The Freedom-K64F is an ultra-low-cost development platform for Kinetis® K64, K63, and K24 MCUs.

* Form-factor compatible with the Arduino® UNO Rev3 pin layout
* Peripherals enable rapid prototyping, including a 6-axis digital accelerometer and magnetometer to create full eCompass capabilities, a tri-colored LED and 2 user push-buttons for direct interaction, a microSD card slot, and connectivity using onboard Ethernet port and headers for use with Bluetooth® and 2.4 GHz radio add-on modules
* OpenSDAv2, the NXP open source hardware embedded serial and debug adapter running an open source bootloader, offers options for serial communication, flash programming, and run-control debugging
The FRDM-K64 is now supported by Arm® Mbed™ OS and Zephyr OS, both open source embedded operating systems for developing the Internet of Things.
![image](https://user-images.githubusercontent.com/94011063/231660418-e5377a42-4fe0-47c1-899c-39499f75a2d5.png)

* pin of FRDM K64F

![image](https://raw.githubusercontent.com/poiudfg/project-use-FRDM-K64F-connect-Multi-functional-shield-/main/frdm_k64f_reve4_header_pinout.jpg)

# Multifunction Shield on FRDM K64F
 This tutorial describes a simple application for measuring temperature using the digital sensor DS18B20 and the Arduino Multifunction Shield connected to FRDM K64F. You can use new feature Expansion Boards (expansion shields) included in the Pins tool v9. This feature enables quick integration of shields in an application without the need to study manuals.

In this paper, you can find the environment setup, 1-wire protocol basics, and the steps of preparing a code with MCUXpresso tools (Peripherals and Pins tool).
![image](https://user-images.githubusercontent.com/94011063/231660867-05a62dc5-0c53-4a69-bb52-3fba6b4f780c.png)

![image](https://user-images.githubusercontent.com/94011063/231660988-0e1b2a60-2f2c-4039-9a6d-2c95cf22bc4c.png)


# So what is this project used for?
In this project we have used to make a countdown clock with the following functions.
code execution
- When Switch 1 is pressed, the loudspeaker will ring randomly from the counted systick value, the LED will light up from top to bottom and
Turn off the 7segment, show the number 4.000 and count down to 0.
- When pressing Switch 2, the speaker will sound randomly from the counted systick value, LED will be on from the 2nd light (from top to bottom).
lower) until the 4th moon and extinguishes the 7segment showing the number 3.000 and counting down until 0
- When pressing Switch 3, the speaker will sound randomly from the counted systick value, LED will be on from the 3rd (from top to bottom)
below) until the 4th moon and extinguishes the 7segment, showing the number 2.000 and counting down until 0
* Each button can interrupt each other
