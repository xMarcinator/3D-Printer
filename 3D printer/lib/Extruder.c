/*
 * Extruder.c
 *
 * Created: 4/18/2021 2:35:30 PM
 *  Author: Marc
 */ 

#include <avr/io.h>
#include "Commander.h"

void setExtruderSpeed(double Distance, unsigned char Speed, unsigned char Filament){	
	setEAxisSpeed(eTiming*Distance/(Filament*Speed));
}

float filament;

#pragma region eAxis
#define EDIR 3
#define ESTEP 1
#define prescaler 3

void initExtruder(){
	// CTC
	TCCR5B |= (1 << WGM52);
	// Prescaler 1
	TCCR5B |= prescaler;
	// Output Compare Match A Interrupt Enable
	TIMSK5 |= (1 << OCIE5A);
	
	DDRC |= (1<<EDIR) | (1<<ESTEP);
	/* Replace with your application code */
	PORTC |= 1<<EDIR;
}

ISR(TIMER5_COMPA_vect)
{
	PORTC ^= (1<<ESTEP);
	
	if(PORTC & (1<<ESTEP)){
		filament -= 0.00125;
		if(filament <= 0.000625){
			TIMSK5 &= ~(1<<OCIE5A); //stop interrupt
		}
	}
}

void setEAxisSpeed(double speed){
	OCR5C = speed;
	
	unsigned char bit = (speed<0);
	
	PORTC = (PORTK&(~(1&(~bit))<<EDIR)) | bit<<EDIR;
	
	TIMSK5 |= (1<<OCIE5A);
}
#pragma endregion eAxis
