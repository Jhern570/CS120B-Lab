/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #9  Exercise # 3
 *	Demo: https://youtu.be/wOhJgeXg2e4 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#include "../header/timer.h"
#include "../header/io.h"
#endif

enum States{start, wait,on,release}state;
double notes[] = {293.66,440.00,440.00,349.23,329.63,329.63,329.63,329.63,349.23,293.66,440.00,440.00,349.23,329.63,329.63,329.63,329.63,349.23,293.66,440.00,440.00,349.23,329.63,329.63,329.63,329.63,349.23,293.66,440.00,440.00,349.23};
unsigned char tempo[] = {20,14,14,14,14,14,14,6,6,20,14,14,14,14,14,14,6,6,20,14,14,14,14,14,14,6,6,20,20,20,20};
unsigned char i;
unsigned char t;
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
				t = 0;
				set_PWM(notes[t]);
				state = on;
			}
			break;
		case on:
			i++;
			if(button == 1 && t < 41){
				if(i <= tempo[t]){
					set_PWM(notes[t]);
				}
				else{
				   if(i <= (tempo[t] + 2)){
				       	set_PWM(0);
				   }
				   else{
					   i = 0;
					   t++;
					   set_PWM(notes[t]);
				   }
				}
				state = on;
			}
			else if(button == 0 &&  t < 41){
				if(i <= tempo[t]){
                                        set_PWM(notes[t]);
                                }
                                else{
                                   if(i <= (tempo[t] + 2)){
                                        set_PWM(0);
                                   }
                                   else{
                                           i = 0;
                                           t++;
					   set_PWM(notes[t]);
                                   }
                                }

				state = release;
			}
			else if(t > 40){
				set_PWM(0);
				state = wait;
			}
			break;
		case release:
			i++;
			if(button == 0 && t < 41){
				if(i <= tempo[t]){
                                        set_PWM(notes[t]);
                                }
                                else{
                                   if(i <= (tempo[t] + 2)){
                                        set_PWM(0);
                                   }
                                   else{
                                           i = 0;
                                           t++;
					   set_PWM(notes[t]);
                                   }
                                }

				state = release;
			}
			else if(t > 40){
				set_PWM(0);
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
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(25);
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

