/*	Author: Julio Hernandez <jhern570@ucr.edu> 
 *	Lab Section: 023
 *	Assignment: Lab #7  Exercise # 2
 *      DEMO: https://youtu.be/Q2pclMeS3v4 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#include "../header/timer.h"
#include "../header/io.h"
#endif

enum States{start, on1, on2, on3, press, release}state;
unsigned char tmpB = 0x00;
unsigned char cnt = 0;
unsigned char button;
unsigned char i;
void Tick(){
        button = ~(PINA);
        switch(state){
                case start:
                        PORTB = 0x01;
                        i = 0;
			LCD_WriteData(cnt + '0');
                        state = on1;
                        break;
                case on1:
                        PORTB = 0x01;
                        i = 1;
                        if(button == 1){
				if(cnt != 0 ){
					cnt--;
					LCD_ClearScreen();
					LCD_WriteData(cnt + '0');
				}
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
                                if(cnt == 10){
                                        cnt = 0;
                                        LCD_ClearScreen();
                                        LCD_WriteData(cnt + '0');
                                }

				state = on2;
                        }
                        else if(button == 1 && i == 3){
                                state = on3;
                        }
                        break;
                case on2:
                        PORTB = 0X02;
                        if(button == 1){
				cnt++;
				if(cnt < 10){
					LCD_ClearScreen();
					LCD_WriteData(cnt + '0');
				}
				else if(cnt == 10){
					LCD_ClearScreen();
					LCD_DisplayString(1, "YOU\'VE WON!!! XD");
				}	
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
				if(cnt != 0 ){
                                        cnt--;
                                        LCD_ClearScreen();
                                        LCD_WriteData(cnt + '0');
                                }
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
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00; 
    DDRD = 0xFF; PORTD = 0x00;
    TimerSet(300);
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

