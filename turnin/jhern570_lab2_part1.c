/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #2  Exercise #1
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#endif

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
    unsigned char tmpB = 0x00;
    unsigned char tmpA0 = 0x00;
    unsigned char tmpA1 = 0x00;

    while (1) {
	//1) Read input 
	tmpA0 = PINA & 0x01; //check if garage is open 
	tmpA1 = PINA & 0x02; // check if light sensor is on

	//2)Perform computation
	//if PA0 is 1, set PB1PB0 = 01, else = 10
	if (tmpA0 == 0x01 && tmpA1 != 0x02){ // True if PA0 is 1
    		tmpB = 0x01;
	}
	else{
		tmpB = 0x00;
	}
	//3) Write output
	
	PORTB = tmpB;
    }
    return 1;
}
