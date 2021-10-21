/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #6  Exercise # 1
 *      DEMO: https://youtu.be/x4WvjEpRJNU 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#include "../header/timer.h"
#endif

enum States{start, on1, on2, on3}state;
unsigned char tmpB = 0x00;
unsigned char i;
void Tick(){
	switch(state){
		case start:
			PORTB = 0x01;
			state = on1;
			break;
		case on1:
		 	PORTB = 0x01;
		        state = on2;
			break;
		case on2:
			PORTB = 0X02;
			state = on3;
			break;
		case on3:
			PORTB = 0x04;
			state = on1;
			break;
		default:
			state = start;
			break;
	}
}

int main(void) {
    DDRB = 0xFF; 
    PORTB = 0x00;
    TimerSet(1000);
    TimerOn();
    state = start;
    while (1) {
        Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }

    return 1;
}

