/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #9  Exercise # 1
 *	Demo: 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#include "../header/timer.h"
#include "../header/io.h"
#endif

enum States{start, press0, release, press1, press2}state;

unsigned char button;
void set_PWM(double frequency){
	static double current_frequency;

	if(frequency != current_frequency){
		if(!frequency) { TCCR3B &= 0x08; }
		else { TCCR3B |= 0x03; }

		if(frequency < 0.954) { OCR3A = 0xFFFF; }
		else if(frequency > 31250) { OCR3A = 0x0000; }
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on(){
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);

	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

void Tick(){
	button = ~(PINA);

	switch(state){
		case start:
			state = release;
		        break;
		case release:
			if(button == 0){
				state = release;
			}
			else if(button == 1){
				set_PWM(261.63);
				state = press0;
			}
			else if(button == 2){
				set_PWM(293.66);
				state = press1;
			}
			else if(button == 4){
				set_PWM(329.63);
				state = press2;
			}
			break;
		case press0:
			if(button == 1){
				state = press0;
			}
			else if(button == 0){
				set_PWM(0);
				state = release;
			}
			break;
		case press1:
			if(button == 2){
				state = press1;
			}
			else if(button == 0){
				set_PWM(0);
				state = release;
			}
			break;
		case press2:
			if(button == 4){
				state = press2;
			}
			else if(button == 0){
				set_PWM(0);
				state = release;
			}
			break;
		default:
			state = start;
			break;
	}
}
	       			       

int main(void) {
    //C4 = 261.63 D4 = 293.66 E4 = 329.63
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(100);
    TimerOn();
    PWM_on();
    state = start;
    button = ~(PINA);
   
    while(1){
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
        	
    }
    return 1;
}

