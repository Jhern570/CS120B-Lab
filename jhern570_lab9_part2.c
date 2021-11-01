/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #9  Exercise # 1
 *	Demo: https://youtu.be/7o5pTMlmU60 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#include "../header/timer.h"
#include "../header/io.h"
#endif

enum States{start, wait,power, up, release, down}state;
double notes[] = {261.63,293.66,329.63,349.23,392.00,440.00,493.88,523.25}; 
unsigned char i;
unsigned char flag;
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
			state = wait;
		        break;
		case wait:
			if(button == 0){
				state = wait;
			}
			else if(button == 1){
				i = 0;
				flag = 1;
				set_PWM(notes[i]);
				state = power;
			}
			break;
		case power:
			if(button == 1){
				state = power;
			}
			else if(button == 0 && flag == 1){
				state = release;
			}
			else if(button == 0 && flag == 0){
				state = wait;
			}
			break;
		case release:
			if(button == 0){
				state = release;
			}
			else if(button == 2){
				if(i != 7){
					i++;
					set_PWM(notes[i]);
				}
				state = up;
			}
			else if(button == 4){
				if(i != 0){
					i--;
					set_PWM(notes[i]);
				}
				state = down;
			}
			else if(button == 1){
				set_PWM(0);
				flag = 0;
				state = power;
			}
		case up:
			if(button == 2){
				state = up;
			}
			else if(button == 0){
				state = release;
			}
			break;
		case down:
			if(button == 4){
				state = down;
			}
			else if(button == 0){
				state = release;
			}
			break;
		default:
			state = start;
			break;
	}
}
	       			       

int main(void) {
   
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

