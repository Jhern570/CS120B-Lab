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

enum States{start, waitPress, pressA0, pressA1,pressBoth}state;
unsigned char tmpC = 0x00;
void Tick(){
	unsigned char tmpC = 0x00;
        switch(state){
              case start:

                        tmpC = 7;
                        PORTC = tmpC;
                        state = waitPress;
                        break;
                case waitPress:
                        if(PINA == 1){
                                if(tmpC != 9){
                                        tmpC++;

                                        PORTC = tmpC;
                                }
                                state = pressA0;
                        }
                        else if(PINA == 2){
                                if(tmpC != 0){
                                        tmpC--;
                                        PORTC = tmpC;
                                }
                                state = pressA1;
                        }
                        else if(PINA == 3){
                                tmpC = 0x00;
                                PORTC = tmpC;
                                state = pressBoth;
                        }
                        else if(PINA == 0){
                                state = waitPress;
                        }
                        break;
                case pressBoth:
			if(PINA == 3){
                                state = pressBoth;
                        }
                        else if(PINA == 1){
                                tmpC++;
                                PORTC = tmpC;
                                state = pressA0;
                        }
                        else if(PINA == 2){
                                state = pressA1;
                        }
                        else if(PINA == 0){
                                state = waitPress;
                        }
                        break;
                case pressA0:
                        if(PINA == 0x01){
                                state = pressA0;

                        }
                        else if(PINA == 2){
                                tmpC--;
                                PORTC = tmpC;
                                state = pressA1;
                        }

                        else if (PINA == 3){
                                tmpC = 0x00;
                                PORTC = tmpC;
                                state = pressBoth;
                        }
                        else if(PINA == 0){
                                state = waitPress;
                        }
                        break;
                case pressA1:
			if(PINA == 2){

                                state = pressA1;

                        }
                        else if(PINA == 1){
                                tmpC++;
                                PORTC = tmpC;
                                state = pressA0;

                        }
                        else if(PINA == 3){
                                tmpC = 0x00;
                                PORTC = tmpC;
                                state = pressBoth;
                        }
                        else if(PINA == 0){
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

