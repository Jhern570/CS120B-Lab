/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #4  Exercise # 3
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#endif

// x = A0, y = A1, # = A2
enum States{start, reset, firstPress, releaseFirst, secondPress, unlock, pressI}state;
unsigned char password  = 0x00;
void Tick(){
       
        switch(state){
		case start:
                        state = reset;
                        break;
                case reset:
			if(PINA < 8 && PINA != 0){
                                state = firstPress;
                        }
			else if(PINA == 8){
				state = pressI;
			}
                        else if(PINA == 0){
                                PORTC = reset;
                                state = reset;
                        }
                        break;
                case firstPress:
                        if(PINA == 4){
                                password = 0x01;
                        }

			if(PINA == 4 || PINA == 2){
				PORTC = firstPress;
                                state =  firstPress;

                        }
                        else if(PINA == 0){
                                state = releaseFirst;
                        }
                        break;
                case releaseFirst:
                        if(PINA){
                                state = secondPress;
                        }
                        else if(PINA == 0){
                                PORTC = releaseFirst;
                                state = releaseFirst;
                        }
                        break;
                case secondPress:
			if(PINA == 2 && password == 1){
				PORTB = 1;
                                password = 0;

                        }
                        else if(PINA != 2 && password == 1){
                                password = 0;
                        }

                        if(PINA == 2){
                                PORTC = secondPress;
                                state = secondPress;
                        }
                        else if(PINA == 0 && PORTB == 1){
                                state = unlock;
                        }
                        else if(PINA == 0 && PORTB == 0){
				password = 0;
                                state = reset;
                        }

                        break;
                case unlock:
                        if(PINA == 8){
                                PORTB = 0x00;
                                state = pressI;
                        }
                        else if(PINA == 0){
				PORTB = 0x01;
                                PORTC = unlock;
                                state = unlock;
                        }
                        break;
                case pressI:
                        if(PINA == 8){
				PORTB = 0x00;
                                PORTC = pressI;
                                state = pressI;
                        }
                        else if(PINA == 0){
                                state = reset;
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
    DDRC = 0xFF; PORTC = 0x00;

    PORTC = 0x00;
    PORTB = 0x00;
    state = start;
    while (1) {
        Tick();
    }

    return 1;
}

