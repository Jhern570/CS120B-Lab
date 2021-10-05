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
	if(x & 0x0200){
		return 9;
	}
	else if(x & 0x0100){
		return 8;
	}
	return 7;
		
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
	if(CheckBit(totalWeight) == 9){
		totalWeight = totalWeight >> 2;
		totalWeight = totalWeight & 0x00FC;
		tmpD = tmpD | totalWeight;
			
	}
	else if(CheckBit(totalWeight) == 8){
		tmpD = ((totalWeight >> 1) & 0x00FC) | tmpD;
	}
	else{
		tmpD = (totalWeight & 0X00FC) | tmpD;
		
	}

	PORTD = tmpD;
	


    }
    return 1;
}
