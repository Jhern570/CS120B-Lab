/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #4  Exercise # 5
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#endif

// x = A0, y = A1, # = A2
//enum States{start, reset, firstPress, releaseFirst, secondPress, unlock, pressI,lock}state;
enum Statew{start, reset, press, release,unlock, pressI}state;
unsigned char password  = 0x00;
unsigned char sequence[4];
unsigned char position = 0x00;
unsignec char pressed = 0x00;
sequence[0] = 4;
sequence[1] = 1;
sequence[2] = 2;
sequence[1] = 1;
void Tick(){
       
        switch(state){
                case start:
			state = reset;
			break;
		case reset:
			if(PINA){
				state = press;		
			}
		
			else if(PINA == 0){
				PORTC = reset;
				state = reset;
			}
			break;
                case press:
			if(PINA == sequence[position] && pressed == 0){
				password = password + 1;
				position = position + 1;
				pressed = 1;
			}
			else if(PINA != sequence[position] && pressed == 0){
				position = position + 1;
				pressed = 1
			}
			
			if(PINA == 0){
				pressed = 0;
				state = release;
			}
			else if(PINA){
				PORTC = press;
				state =  press;
			}
			break;
                case release:
			if(PINA){
				state = press;
			}
			else if(PINA == 0 && position != 4 && password != 4){
				PORTC = release;
				state = release;
			}
			else if(PINA == 0 && position == 4 && password != 4){
				position = 0;
				password = 0;
				state = reset;
			}
			else if(PINA == 0 && position == 4 && password == 4){
				PORTB = 0x01;
				position = 0;
				password = 0;
				state = unlock;
			}
                        break;
               /* case secondPress:
                        if(PINA == 2 && password == 1 && PINB == 0){
                                PORTB = 0x01;
				password = 0;
                                
                        }
			else if(PINA == 2 && password == 1 && PINB == 1){
				PORTB = 0x00;
				password = 0;
			}	
			else if(PINA != 2 && password == 1){
				password = 0;
			}
			
			
			if(PINA){
				PORTC = secondPress;
				state = secondPress;
			}
			else if(PINA == 0 && PINB == 1){
				state = unlock;
			}
			else if(PINA == 0 && PINB == 0){
				state = reset;
			}
				
                        break;*/
		case unlock: 
			if(PINA == 8){
				PORTB = 0x00;
				state = pressI;
			}
			else if(PINA == 0){
				PORTC = unlock;
				state = unlock;
			}
			else if(PINA != 8 && PINA != 0){
				state = press;
			}
			break;	
		case pressI: 
			if(PINA == 8){
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

