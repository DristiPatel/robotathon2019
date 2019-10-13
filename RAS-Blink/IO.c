// IO.c
// This software configures the switch and LED
// You are allowed to use any switch and any LED, 
// although the Lab suggests the SW1 switch PF4 and Red LED PF1
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: March 30, 2018
// Last Modified:  change this or look silly
// Lab number: 7


#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>

//------------IO_Init------------
// Initialize GPIO Port for a switch and an LED
// Input: none
// Output: none
void IO_Init(void) {
 // --UUU-- Code to initialize PF4 and PF2
	SYSCTL_RCGCGPIO_R |= 0x20; //Turn on clock for Port F
	volatile int nop;
	nop++;
	
	
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; //unlock port f
	
	GPIO_PORTF_DIR_R |= 0x04; 
	GPIO_PORTF_DIR_R &= ~(0x10); 
	
	GPIO_PORTF_DEN_R |= 0x14; 
	
	GPIO_PORTF_CR_R = 0xFFFFFFFF;
	GPIO_PORTF_PUR_R |= 0x10; //set Pull Down Resistor
}

//------------IO_HeartBeat------------
// Toggle the output state of the  LED.
// Input: none
// Output: none
void IO_HeartBeat(void) {
 // --UUU-- PF2 is heartbeat
	
	GPIO_PORTF_DATA_R ^= 0x04; //Trigger LED
}


//------------IO_Touch------------
// wait for release and press of the switch
// Delay to debounce the switch
// Input: none
// Output: none
void IO_Touch(void) {
 // --UUU-- wait for release; delay for 20ms; and then wait for press
	while((GPIO_PORTF_DATA_R & 0x10) == 0x10){} 
		
	int delay = 400000; //(80Mhz * 20ms)/4 OR (20ms/12.5ns)/4 - 4 due to 4 instructions per loop
		
	while(delay != 0) 
	{
		delay--;
	}
	while((GPIO_PORTF_DATA_R & 0x10) != 0x10) { } // Waits for a press to leave this function and loop again to output
}  

