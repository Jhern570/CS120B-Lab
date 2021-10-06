/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #3  Exercise # 5
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
    DDRD = 0x00; PORTD = 0xFF;
    DDRB = 0x00; PORTB = 0x01;
    DDRB = 0xFE; PORTB = 0x00;
	
    unsigned char tmpD = 0X00;
    unsigned char firstB = 0x00;
    unsigned char tmpB = 0X00;
    while (1) {

	tmpD = PINA;
	firstB = GetBit(PINB,0);

	if((tmpD * 2) + firstB >= 70){
		tmpB = 0x02;
	}
	else if(((tmpD * 2) + firstB > 5) && ((tmpD* 2) + firstB < 70)){
		tmpB = 0x04;
	}
	else if(((tmpD * 2) + firstB > 5) <= 5){
	       tmpB = 0X00;
	}	       

	PORTB = tmpB;
    }
    return 1;
}

