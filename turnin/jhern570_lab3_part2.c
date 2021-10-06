/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #3  Exercise # 2
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#endif


int main(void) {
    DDRA = 0x00; PORTA = 0x0F;
    DDRC = 0x00; PORTC = 0x00;

    while (1) {
    	
	unsigned char tmpC = 0x00;
	if(PINA <= 2){
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
		
	PORTC = tmpC;	
    }
    return 1;
}

