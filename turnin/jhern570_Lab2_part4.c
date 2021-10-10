/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #2  Exercise # challenge
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#endif


unsigned char CheckBit(unsigned short x){
	return (x >> 2);
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0x00; PORTC = 0xFF;
    DDRD = 0xFF; PORTD = 0x00;

    unsigned char tmpA = 0X00;
    unsigned char tmpB = 0x00;
    unsigned char tmpC = 0x00;
    unsigned char tmpD = 0x00;
    unsigned short totalWeight = 0x0000; 
    unsigned char shiftWt = 0x00;

    while (1){
	
	tmpA = PINA;
	tmpB = PINB;
	tmpC = PIND;
	totalWeight = tmpA + tmpB + tmpC;
	
	if(totalWeight > 140){
		tmpD = 0x01;
	}
	
	if(tmpA > tmpC){
		if((tmpA - tmpC) > 80){
			tmpD = tmpD ^ 0x02;
		}
	}
	else if(tmpC > tmpA){
		if((tmpC - tmpA) > 80){
			tmpD = tmpD ^ 0x02;
		}
	
	}
	
	shiftWt = CheckBit(totalWeight);
	tmpD = tmpD | shiftWt;
	 

	PORTD = tmpD;
	


    }
    return 1;
}
