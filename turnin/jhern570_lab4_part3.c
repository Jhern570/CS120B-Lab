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
enum States{start, waitPress, pressX, pressY, pressP, unlock, pressI}state;
unsigned char password  = 0x00;
void Tick(){
       
        switch(state){
                case start:
			state = waitPress;
			break;
		case waitPress:
			if(PINA == 4){
				if(password == 1){
					password = 0x00;
				}
				else{
					password++;
				}
				state = pressP;		
			}
			else if(PINA == 2){
				if(password == 1){
					PORTB = 0x01;
					password = 0x00;
					state = unlock;
				}
				state = pressY;
				
			}
			else if(PINA == 1){
				if(password == 1){
					password = 0x00;
				}
				state = pressX;
			}
			else{
				PORTC = waitPress;
				state = waitPress;
			}
			break;
                case pressX:
			if(PINA == 1){
				PORTC = pressX;
				state = pressX;
			}
			else if(PINA == 0){
				state = waitPress;
			}
			break;
                case pressY:
			if(PINA == 2){
				PORTC = pressY;
				state = pressY;
			}
			else if(PINA == 0){
				state = waitPress;
			}
                        break;
                case pressP:
                        if(PINA == 2){
                                PORTC = pressP;
				state = pressP;
                                
                        }
			else if(PINA == 0){
				state = waitPress;
			}
                        break;
		case unlock: 
			if(PINA == 8){
				PORTB = 0x00;
				state = pressI;
			}
			else{
				PORTC = unlock;
				state = unlock;
			}
			break;	
		case pressI: 
			if(PINA == 8){
				PORTC = pressI;
				state = pressI;
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

