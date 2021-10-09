/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #2  Exercise #2
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#endif


unsigned char GetBit(unsigned char x, unsigned k){
	return (x & (0x01 << k));
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    

    while (1){
	
	unsigned char i;
   	unsigned char cntavail = 0;
	
	for(i = 0; i < 4; i++){

		if(GetBit(PINA, i)){
			cntavail++;
		}
	}
	
	PORTC = 4 - cntavail;

    }
    return 1;
}
