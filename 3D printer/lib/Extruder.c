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
	// sæt prescaleren
	TCCR5B |= prescaler;
	// Sæt mode til Output Compare Match
	TIMSK5 |= (1 << OCIE5A);
	//sæt pins til output
	DDRC |= (1<<EDIR) | (1<<ESTEP);
	//tænd for extruder pins
	PORTC |= 1<<EDIR;
}

ISR(TIMER5_COMPA_vect)
{
	//flip step
	PORTC ^= (1<<ESTEP);
	//kun tæl ned hver anden gang
	if(PORTC & (1<<ESTEP)){
		//ændre positionen;
		filament -= 0.00125;
		//tjek om man er kommet tæt nok på
		if(filament <= 0.000625){
			TIMSK5 &= ~(1<<OCIE5A); //stop interrupt
		}
	}
}

void setEAxisSpeed(double speed){
	//tjek om aksen skal flytte sig
	if(speed != 0){
		//sæt hastigheden
		OCR5C = speed;
		//find ud af hvilken retning den skal køre.
		unsigned char bit = (speed<0);
		//sæt biten
		PORTC = (PORTK&(~(1&(~bit))<<EDIR)) | bit<<EDIR;
		//tænd for timeren
		TIMSK5 |= (1<<OCIE5A);
	}	
}
#pragma endregion eAxis
