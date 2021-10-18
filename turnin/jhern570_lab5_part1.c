/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #5  Exercise # 1
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
    DDRC = 0xFF; PORTC = 0x00;

    while (1) {
    	
	unsigned char tmpC = 0x00;
	unsigned char button = ~PINA;
	if(button == 0){
		tmpC = 0x40;
	}
	else if(button == 1 || button ==  2){
		tmpC = 0x60;
	}
	else if(button == 3 || button == 4){
		tmpC = 0x70;
	}
	else if(button == 5 || button == 6){
		tmpC = 0x38; 
	}
	else if(button >= 7 && button <= 9){
		tmpC = 0x3C;
	}
	else if(button >= 10 && button <= 12){
		tmpC = 0x3E;
	}
	else{
		tmpC = 0x3F;
	}
		
	PORTC = tmpC;	
    }
    return 1;

}

