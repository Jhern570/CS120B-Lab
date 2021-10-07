/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #3  Exercise # 3
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#endif

unsigned char GetBit(unsigned char x, unsigned char k){
	return (x & (0x01 << k));
}

int main(void) {
    DDRA = 0x10; PORTA = 0x7F;
    DDRC = 0x00; PORTC = 0x00;

    while (1) {
    	
	unsigned char tmpC = 0x00;
	if(PINA == 0){
		tmpC = 0x04;
	}
	else if(PINA == 1 || PINA == 2){
		tmpC = 0x60;
	}
	else if(PINA == 3 || PINA == 4){
		tmpC = 0x70;
	}
	else if(PINA == 5 || PINA == 6){
		tmpC = 0x38; 
	}
	else if(PINA >= 7 &&PINA <= 9){
		tmpC = 0x3C;
	}
	else if(PINA >= 10 && PINA <= 12){
		tmpC = 0x3E;
	}
	else{
		tmpC = 0x3F;
	}

	if(!GetBit(PINA,6)){
			if(GetBit(PINA, 4) && GetBit(PINA,5)){
				tmpC = tmpC ^ 0x80;
		}
	}
		
	PORTC = tmpC;	
    }
    return 1;
}

