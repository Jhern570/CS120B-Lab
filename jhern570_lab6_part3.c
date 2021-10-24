/*	Author: Julio Hernandez <jhern570@ucr.edu> 
 *	Lab Section: 023
 *	Assignment: Lab #6  Exercise # 3
 *      DEMO: https://youtu.be/-dNnTIVDfqs 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#include "../header/timer.h"
#endif

enum States{start, wait, press0, press1, pressBoth}state;
unsigned char tmpB = 0x00;
unsigned char button;
unsigned char i;
void Tick(){
	button = ~(PINA);
	switch(state){
		case start:
			tmpB = 0x07;
			PORTB = tmpB;
			state = wait;
			break;
		case wait:
		        if(button == 1 ){
				if(tmpB != 9){
					tmpB++;
					PORTB = tmpB;
				}
				i = 0;
			       	state = press0;
			}
			else if(button == 2){
				if(tmpB != 0){
					tmpB--;
					PORTB = tmpB;
				}
				i = 0;
				state = press1;
			}
			else if(button == 3){
				tmpB = 0;
				PORTB = tmpB;
				state = pressBoth;
			}
			else if(button == 0){
				state = wait;
			}
			break;
		case pressBoth:
			if(button == 3){
				state = pressBoth;
			}
			else if(button == 1){
				tmpB++;
				PORTB = tmpB;
				i = 0;
				state = press0;
			}
			else if(button == 2){
				i = 0;
				state = press1;
			}
			else if(button == 0){
				state = wait;
			}
			break;
		case press0:
			i++;
			if(button == 1){
				if(tmpB != 9 && i > 10){
					i = 0;
					tmpB++;
					PORTB = tmpB;
				}
				state = press0;
			}
			else if(button == 2){
				tmpB--;
				PORTB = tmpB;
				i = 0;
				state = press1;
			}
			else if(button == 3){
				tmpB = 0;
				PORTB = tmpB;
                                state = pressBoth;
                        }
			else if(button == 0){
                                state = wait;
                        }
			break;
		case press1:
			i++;
			if(button == 2){ 
				if(tmpB != 0 && i > 10){
					i = 0;
					tmpB--;
					PORTB = tmpB;
				}
                                state = press1;
                        }
                        else if(button == 1) {
				i = 0;
                                tmpB++;
				PORTB = tmpB;
				state = press0;
                        }
			else if(button == 3){
				tmpB = 0;
				PORTB = tmpB;
				state = pressBoth;
			}
			else if(button == 0){
				state = wait;
			}
			break;
		default:
			state = start;
			break;
	}
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF; 
    DDRB = 0xFF;  PORTB = 0x00;
    TimerSet(100);
    TimerOn();
    state = start;
    while (1) {
        Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }

    return 1;
}

