/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #10  Exercise # 4
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

enum ThreeLEDsSM{start_t, first, second, third}TLSstate;
enum BlinkingLEDSM{start_b, on, off}Bstate;
enum CombineLEDSM{start_c,combine}Cstate;
enum SpeakerSM{start_s, wait, press, release}Sstate;
enum FrequencySM{start_f, wait_f, press_f}Fstate;
unsigned char threeLEDs;
unsigned char blinkingLED;
unsigned char button;
unsigned char i;
unsigned char f;
unsigned char sound;
void ThreeLED(){
	switch(TLSstate){
		case start_t:
			threeLEDs = 0;
			TLSstate = first;
			break;
		case first:
			threeLEDs = 1;
			TLSstate = second;
			break;
		case second:
		       	threeLEDs = 2;
			TLSstate = third;
			break;
		case third:
			threeLEDs = 4;
			TLSstate = first;
			break;
		default:
			TLSstate = start_t;
			break;
	}
}

void BlinkingLED(){
	switch(Bstate){
		case start_b:
			blinkingLED = 0;
			Bstate = on;
			break;
		case on:
			blinkingLED = 8;
			Bstate = off;
			break;
		case off: 
			blinkingLED = 0;
			Bstate = on;
			break;
		default:
			Bstate = start_b;
	}
}

void Speaker(){
	button = ~(PINA);
	switch(Sstate){
		case start_s:
			Sstate = wait;
		        break;
		case wait:
			if(button == 4){
				i = 0;
				sound = 16;
				Sstate = press;
			}
			break;
		case press:
			i++;	
			if(button == 4){
				if (i < f){
					sound = 16;
				}
				else if (i < f + 2){
					sound = 0;
				}
				else{
					i = 0;
				}
				Sstate = press;
			}
			else if(button == 0){
				sound = 0;
				Sstate = wait;
			}
			break;
		default:
			Sstate = start_s;
	}
}
			
void Frequency(){
	button = ~(PINA);
	switch(Fstate){
		case start_f:
			f = 2;
			Fstate = wait_f;
			break;
		case wait_f:
			if(button == 1){
				f++;
				Fstate = press_f;
			}
			else if(button == 2){
				if(f != 2){
					f--;
				}
				Fstate = press_f;
			}
			break;
		case press_f:
			if (button == 1 || button == 2){
				Fstate = press_f;
			}
			else if(button == 0){
				Fstate = wait_f;
			}
			break;
		default:
			Fstate = start_f;
	}
}

				

void CombineLEDs(){
	switch(Cstate){
		case start_c:
			Cstate = combine;
			break;
		case combine:
			PORTB = (threeLEDs | blinkingLED) | sound;
			Cstate = combine;
			break;
			
		default:
			Cstate = start_c;
			break;
	}
}


	

int main(void){	
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    unsigned short elapsedTime_threeLEDs = 300;
    unsigned short elapsedTime_blinkingLED = 1000; 
    unsigned short timePeriod = 1;
    TimerSet(timePeriod);
    TimerOn();
    TLSstate = start_t;
    Bstate = start_b;
    Cstate = start_c;
    
    while(1){
	Frequency();
	Speaker();
	if(elapsedTime_threeLEDs >= 300){
		ThreeLED();
		elapsedTime_threeLEDs = 0;
		
	}
	if(elapsedTime_blinkingLED >= 1000){
		BlinkingLED();
		elapsedTime_blinkingLED = 0;
	}
       /* if(elapsedTime_threeLEDs == 0 || elapsedTime_blinkingLED == 0){
			CombineLEDs();
	}*/
	CombineLEDs();
	while(!TimerFlag);
	TimerFlag = 0;
	elapsedTime_threeLEDs += timePeriod;
	elapsedTime_blinkingLED += timePeriod;
		
    }
    return 1;
}

