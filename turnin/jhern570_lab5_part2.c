/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #5  Exercise # 2
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#endif


enum States{start, waitPress, pressA0, pressA1,pressBoth}state;
unsigned char tmpC = 0x00;
unsigned char button = 0x00;
void Tick(){
	button = ~(PINA);
        switch(state){
              case start:

                        tmpC = 7;
                        PORTC = tmpC;
                        state = waitPress;
                        break;
                case waitPress:
                        if(button == 1){
                                if(tmpC != 9){
                                        tmpC++;

                                        PORTC = tmpC;
                                }
                                state = pressA0;
                        }
                        else if(button == 2){
                                if(tmpC != 0){
                                        tmpC--;
                                        PORTC = tmpC;
                                }
                                state = pressA1;
                        }
                        else if(button == 3){
                                tmpC = 0x00;
                                PORTC = tmpC;
                                state = pressBoth;
                        }
                        else if(button == 0){
                                state = waitPress;
                        }
                        break;
                case pressBoth:
			if(button == 3){
                                state = pressBoth;
                        }
                        else if(button == 1){
                                tmpC++;
                                PORTC = tmpC;
                                state = pressA0;
                        }
                        else if(button == 2){
                                state = pressA1;
                        }
                        else if(button == 0){
                                state = waitPress;
                        }
                        break;
                case pressA0:
                        if(button == 0x01){
                                state = pressA0;

                        }
                        else if(button == 2){
                                tmpC--;
                                PORTC = tmpC;
                                state = pressA1;
                        }

                        else if (button == 3){
                                tmpC = 0x00;
                                PORTC = tmpC;
                                state = pressBoth;
                        }
                        else if(button == 0){
                                state = waitPress;
                        }
                        break;
                case pressA1:
			if(button == 2){

                                state = pressA1;

                        }
                        else if(button == 1){
                                tmpC++;
                                PORTC = tmpC;
                                state = pressA0;

                        }
                        else if(button == 3){
                                tmpC = 0x00;
                                PORTC = tmpC;
                                state = pressBoth;
                        }
                        else if(button == 0){
                                state = waitPress;
                        }
                        break;
                default:
                        state = start;
                        break;
      }
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

   
    PORTC = 0x00;
    state = start;
    while (1) {
        Tick();
    }

    return 1;
}

