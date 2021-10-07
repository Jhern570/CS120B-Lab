/*	Author: Julio Hernandez
 *  Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#endif

enum States{start, releaseOff, pressOn, releaseOn, pressOff}state;

void Tick(){
	switch(start){
		case start:
			state = releaseOff;
			PORTB = 0x01;
			break;
		case releaseOff: 
			if(PINA){
				PORTB = 0x02;
				state = pressOn;
			}
			else{
				state = releaseOff;
			}
			break;
		case pressOn:
			state = PINA ? pressOn : releaseOn;
			break;
		case releaseOn:
			if(!PINA){
				state = releaseOn;
			}
			else{
				PORTB = 0X01;
				state = pressOff;
			}
			break;
		case pressOff: 
			state = PINA ? pressOff : releaseOff;
			break;
		default:
			state = start;
			break;
	}
}

int main(void) {
    DDRA = 0xFE; PORTA = 0x01;
    DDRB = 0xFF; PORTB = 0x00;
    
    PORTB = 0x00;
    state = start;
    while (1) {
	Tick();
    }
    return 1;
}
