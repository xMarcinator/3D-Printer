/*
 * 3D printer.c
 *
 * Created: 15/03/2021 10.54.34
 * Author : Marc
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lib/Vectors.h"
#include "lib/Commander.h"

//#define XDIR 1
//#define XSTEP 0
//
//void FOO(){
	//// CTC
	//TCCR1B |= (1 << WGM12);
	//// Prescaler 1
	//TCCR1B |= 3;
	//// Output Compare Match A Interrupt Enable
	//TIMSK1 |= (1 << OCIE1A);
	//
	//DDRF |= (1<<XDIR) | (1<<XSTEP);
	///* Replace with your application code */
	//PORTF = (1<<XDIR);
//}	
//
//double toMove;
//
//ISR(TIMER1_COMPA_vect)
//{
	//PORTF ^= (1<<XSTEP);
	//
	//if(PORTF & (1<<XSTEP)){
		//toMove -= 0.00125;
		//if(toMove <= 0.000625){
			//TIMSK1 &= ~(1<<OCIE1A); //stop interupt
		//}
	//}
//}


int main(void)
{
	initCommander();
	
	Vector toMove;
	toMove.x = 100;
	toMove.y = 100;
	toMove.z = 0;	
	
	//toMove = 10000;
	//
	//FOO();
	moveLinear(toMove);
	//OCR1A = 1000;
	
    while (1) {
	    
    }
	
	return 0;
}



