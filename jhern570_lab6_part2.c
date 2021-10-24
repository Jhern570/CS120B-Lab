/*	Author: Julio Hernandez <jhern570@ucr.edu>
 *	Lab Section: 023
 *	Assignment: Lab #6  Exercise # 2
 *      DEMO: https://youtu.be/plofvTN-SzA 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#include "../header/timer.h"
#endif

enum States{start, on1, on2, on3, press, release}state;
unsigned char tmpB = 0x00;
unsigned char button;
unsigned char i;
void Tick(){
        button = ~(PINA);
        switch(state){
                case start:
                        PORTB = 0x01;
                        i = 0;
                        state = on1;
                        break;
                case on1:
                        PORTB = 0x01;
                        i = 1;
                        if(button == 1){
                                state = press;
                        }
                        else{
                                state = on2;
                                i++;
                        }
                        break;
                case press:
                        if(button == 1){
                                state = press;
                        }
                        else{
                                state = release;
                        }
                        break;
		case release:
                        if(button == 0){
                                state = release;
                        }
                        else if(button == 1 && i == 1){
                                state = on1;
                        }
                        else if(button == 1 && (i == 2 || i == 4)){
                                state = on2;
                        }
                        else if(button == 1 && i == 3){
                                state = on3;
                        }
                        break;
                case on2:
                        PORTB = 0X02;
                        if(button == 1){
                                state = press;
                        }
                        else if(button == 0 && i == 2) {
                                state = on3;
                                i++;
                        }
                        else if(button == 0 && i == 4){
                                state = on1;
                        }
                        break;
                case on3:
                        PORTB = 0x04;
                        if(button == 1){
                                state = press;
                        }
                        else{
                                state = on2;
                                i++;
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
    TimerSet(300);
    TimerOn();
    state = start;
    while (1) {
        Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }

    return 1;
}

