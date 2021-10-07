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
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0x00; PORTC = 0x00;

    while (1) {
    	unsigned char lvl = 0x00;
        unsigned char bit = 0x00;
        unsigned char i;
        for(i = 0; i < 4; i++){
                if(GetBit(PINA,i)){
                        bit = GetBit(PINA,i);
                        lvl = lvl ^ bit;
                }
        }
	unsigned char tmpC = 0x00;
	if(lvl == 0){
		tmpC = 0x04;
	}
	else if(lvl == 1 || lvl == 2){
		tmpC = 0x60;
	}
	else if(lvl == 3 || lvl == 4){
		tmpC = 0x70;
	}
	else if(lvl == 5 || lvl == 6){
		tmpC = 0x38; 
	}
	else if(lvl >= 7 && lvl <= 9){
		tmpC = 0x3C;
	}
	else if(lvl >= 10 && lvl <= 12){
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

