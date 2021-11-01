/*	Author: Julio Hernandez 
 *	Lab Section: 023
 *	Assignment: Lab #8  Exercise # 2
 *	Demo: https://youtu.be/XcwI1dzjOEY 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "../header/simAVRHeader.h"
#include "../header/timer.h"
#include "../header/io.h"
#endif

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}
     
int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    unsigned char tmpD;
    unsigned char tmpB;
    unsigned short x;
    ADC_init();
  

    while(1){
	  x = ADC;
          tmpB = (char)x;
	  tmpD = (char)(x >> 8);
          PORTB = tmpB;
	  PORTD = tmpD;
	 
    }

    return 1;
}

