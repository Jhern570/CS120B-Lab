/*	Author: Julio Hernandez <jhern570@ucr.edu> 
 *	Lab Section: 023
 *	Assignment: Lab #7  Exercise # 1
 *      DEMO: https://youtu.be/e4UWjO_dXNI 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#include "../header/timer.h"
#include "../header/io.h"
#endif


enum States{start, wait, press0, press1, pressBoth}state;
unsigned char cnt = 0;
unsigned char button;
unsigned char i;
void Tick(){
	button = ~(PINA);
	switch(state){
		case start: 
			LCD_WriteData(cnt + '0');
			state = wait;
		case wait:
			if(button == 1){
				if(cnt != 9){
					cnt++;
					LCD_ClearScreen();
					LCD_WriteData(cnt + '0');
				}
				i = 0;
				state = press0;
			}
			else if(button == 2){
				if(cnt != 0){
					cnt--;
					LCD_ClearScreen();
					LCD_WriteData(cnt + '0');
				}
				i = 0;
				state = press1;
			}
			else if(button == 3){
				cnt = 0;
				LCD_ClearScreen();
				LCD_WriteData(cnt + '0');
				state = pressBoth;
			}
			else if(button == 0){
				state = wait;
			}
			break;
		case pressBoth:
			if(button == 3){
				state = pressBoth;
			}
			else if(button == 1){
				cnt++;
				LCD_ClearScreen();
				LCD_WriteData(cnt + '0');
				i = 0;
				state = press0;
			}
			else if(button == 2){
				i = 0;
				state = press1;
			}
			else if(button == 0){
				state = wait;
			}
			break;
		case press0:
			i++;
			if(button == 1){
				if(cnt != 9 && i > 10){
					i = 0;
					cnt++;
					LCD_ClearScreen();
					LCD_WriteData(cnt + '0');
				}
				state = press0;
			}
			else if(button == 2){
				cnt--;
				LCD_ClearScreen();
				LCD_WriteData(cnt + '0');
				i = 0;
				state = press1;
			}
			else if(button == 3 ){
				cnt = 0;
				LCD_ClearScreen();
				LCD_WriteData(cnt + '0');
				state = pressBoth;
			}
			else if(button == 0){
				state = wait;
			}
			break;
		case press1:
			i++;
			if(button == 2){
				if(cnt != 0 && i > 10){
					i = 0;
					cnt--;
					LCD_ClearScreen();
					LCD_WriteData(cnt + '0');
				}
				state = press1;
			}
			else if(button == 1){
				i = 0;
				cnt++;
				LCD_ClearScreen();
				LCD_WriteData(cnt + '0');
				state = press0;
			}
			else if(button == 3){
				cnt = 0;
				LCD_ClearScreen();
				LCD_WriteData(cnt + '0');
				state = pressBoth;
			}
			else if(button == 0){
				state = wait;
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
    DDRD = 0xFF; PORTD = 0x00;
    TimerSet(100);
    TimerOn();
    state = start;
    //Initialize the LCD display
    LCD_init();

   
    while (1) {
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }

    return 1;
}

