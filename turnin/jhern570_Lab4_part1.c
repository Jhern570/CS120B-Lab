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
				PORTB = 0x01;
                                state = releaseOff;

                        }
                        break;
                case pressOn:
			PORTB = 0x02;
                        state = PINA ? pressOn : releaseOn;
                        break;
                case releaseOn:
                        if(!PINA){
                                state = releaseOn;
                        }
                        else{
                                PORTB = 0x01;
                                state = pressOff;
                        }
                        break;
                case pressOff:
			PORTB = 0x01;
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

