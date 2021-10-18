/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #5  Exercise # 3
 *      DEMO: https://youtu.be/x4WvjEpRJNU 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#endif


enum States{start, press, release,off}state;
unsigned char button = 0x00;
unsigned char cnt = 0;
void Tick(){
	button = ~(PINA);
        switch(state){
              case start:

                        PORTC = 0x00;
                        state = off;
                        break;
                case off:
                        if(button == 1){
                                PORTC = 0X21;
                                state = press;
				cnt++;
                        }
                        else if(button == 0){
                                state = off;
                        }
                        break;
                case press:
			if(button == 1){
                                state = press;
                        }
                        else if(button == 0 && cnt != 0){
                                state = release;
                        }
			else if(button == 0 && cnt == 0){
				state = off;
			}
                        break;
                case release:
                        if(button == 0x01 && (cnt == 1 || cnt == 8)){
                                PORTC = 0x12;
				cnt++;
				state = press;

                        }
                        else if(button == 0x01 && (cnt == 2 || cnt == 7)){
                                PORTC = 0x0C;
                                cnt++;
                                state = press;
                        }

                        else if (button == 0x01 && (cnt == 3 || cnt == 10)){
                                PORTC = 0x2D;
                                cnt++;
                                state = press;
                        }
                        else if(button == 0x01 && cnt == 4){
                                PORTC = 0x1E;
                                cnt++;
                                state = press;
                        }
			else if(button == 0x01 && (cnt == 5 || cnt == 12)){
				PORTC = 0x3F;
                                cnt++;
                                state = press;
			}
			else if(button == 0x01 && (cnt == 6 || cnt == 13)){
				PORTC = 0x00;
				cnt = (cnt == 13) ? 0 : cnt + 1;
				state = press;
			}
			else if(button == 0x01 && cnt == 9){
				PORTC = 0x21;
				cnt++;
				state = press;
			}
			else if(button == 0x01 && cnt == 11){
				PORTC = 0X33;
				cnt++;
				state = press;
			}
			else if (button == 0){
				state = release;
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

