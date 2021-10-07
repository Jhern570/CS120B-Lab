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

enum States{start, depress, pressA0, pressA1}state;

void Tick(){
	unsigned char tmpC = 0x00;
        switch(state){
                case start:
                        state = depress;
			tmpC = 0x07;
			PORTC = tmpC;
						
                        break;
                case depress:
			if(PINA == 0x01){
				tmpC++;
				PORTC = tmpC;
				state = pressA0;
			}
			else if(PINA == 0x02){
				tmpC--;
				PORTC = tmpC;
				state = pressA1;
			}
			else{
				PORTC = 0x00;
				state = depress;
			}
			break;
                case pressA0:
			if(PINA){
				if(tmpC != 0x09){
					tmpC++;
					PORTC = tmpC;
					state = pressA0;
				}

			}
			else{
				state = depress;
			}

                        break;
                case pressA1:
                        if(PINA == 0x02){
                                if(tmpC != 0x00){
                                        tmpC++;
                                        PORTC = tmpC;
                                       
                                }
				state = pressA1;
                                
                        }
                        else{
                                state = depress;
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

