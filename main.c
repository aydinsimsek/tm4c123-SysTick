#include "TM4C123.h"
#include <stdint.h> 

int main()
{
	SysTick->CTRL = 0x0; // Disable SysTick during setup 
	SysTick->LOAD = 4000000; // Initial counter value for 1 sec since the clock period is 250 ns  
	SysTick->VAL = 0x0; // Clear the COUNT bit of the CTRL register 
	SysTick->CTRL = 0x3; // Enable timer, interrupt, use PIOSC as clock source 	
	SYSCTL->RCGCGPIO |= 0x20; //Enable the clock to PortF 
	GPIOF->DIR |= 0x2; // Configure PF1 to be an output
  GPIOF->DEN |= 0x2; // Enable digital functions for PF1
	GPIOF->DATA &= 0xFD; // Turn off the red LED(which is connected to PF1)   
	while(1); // Wait for interrupt
	return 0; 
}

void SysTick_Handler()
{
	GPIOF->DATA = ~GPIOF->DATA; // Toggle the red LED  
}