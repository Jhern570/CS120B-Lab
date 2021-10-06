/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #3  Exercise # 1
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
    DDRB = 0x00; PORTB = 0xFF;

    DDRC = 0xFF; PORTC = 0x00;
    while (1) {
    	unsigned char i;
	unsigned char cnt1 = 0;
	for(i = 0; i < 8; i++){
		if(GetBit(PINA, i)){
			cnt1++;
		}
		if(GetBit(PINB, i)){
			cnt1++;
		}
	}
	PORTC = cnt1;	
    }
    return 1;
}

