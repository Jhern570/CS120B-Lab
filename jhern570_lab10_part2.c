/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #10  Exercise # 2
 *	Demo: https://youtu.be/nZiTLzLkBtk
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
unsigned char threeLEDs;
unsigned char blinkingLED;
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

void CombineLEDs(){
	switch(Cstate){
		case start_c:
			Cstate = combine;
			break;
		case combine:
			PORTB = (threeLEDs | blinkingLED);
			Cstate = combine;
			break;
			
		default:
			Cstate = start_c;
			break;
	}
}


	

int main(void){	
    DDRB = 0xFF; PORTB = 0x00;
    unsigned short elapsedTime_threeLEDs = 300;
    unsigned short elapsedTime_blinkingLED = 1000; 
    unsigned short timePeriod = 100;
    TimerSet(timePeriod);
    TimerOn();
    TLSstate = start_t;
    Bstate = start_b;
    Cstate = start_c;
    
    while(1){
	if(elapsedTime_threeLEDs >= 300){
		ThreeLED();
		elapsedTime_threeLEDs = 0;
		
	}
	if(elapsedTime_blinkingLED >= 1000){
		BlinkingLED();
		elapsedTime_blinkingLED = 0;
	}
        if(elapsedTime_threeLEDs == 0 || elapsedTime_blinkingLED == 0){
			CombineLEDs();
	}
	while(!TimerFlag);
	TimerFlag = 0;
	elapsedTime_threeLEDs += timePeriod;
	elapsedTime_blinkingLED += timePeriod;
		
    }
    return 1;
}
