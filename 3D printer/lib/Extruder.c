/*
 * Extruder.c
 *
 * Created: 4/18/2021 2:35:30 PM
 *  Author: Marc
 */ 
#define eRotation 1
#define eSteps 200 
#define eMicro 16
#define eScaler 64
#define eSpeed F_CPU * eRotation /(eSteps*eMicro*eScaler)

#include <avr/io.h>

void setExtruderSpeed(unsigned char Distance, unsigned char Speed, unsigned char Filament){	
	setEAxisSpeed(eSpeed*Distance/(Filament*Speed));
}



#pragma region eAxis
#define EDIR 6
#define ESTEP 4
#define prescaler 3

void initExtruder(){
	// CTC
	TCCR5B |= (1 << WGM52);
	// Prescaler 1
	TCCR5B |= prescaler;
	// Output Compare Match A Interrupt Enable
	TIMSK5 |= (1 << OCIE5A);
	
	DDRL |= (1<<EDIR) | (1<<ESTEP);
	/* Replace with your application code */
	PORTL |= 1<<EDIR;
}

ISR(TIMER5_COMPA_vect)
{
	PORTL ^= (1<<ESTEP);
	
	if(PORTL & (1<<ESTEP)){
		ToMove.x -= 0.00125;
		if(ToMove.x <= 0.000625){
			TIMSK5 &= ~(1<<OCIE5A); //stop interrupt
		}
	}
}

void setEAxisSpeed(double speed){
	OCR5C = speed;
	
	unsigned char bit = (speed<0);
	
	PORTL = (PORTL&(~(1&(~bit))<<EDIR)) | bit<<EDIR;
	
	TIMSK5 |= (1<<OCIE5A);
}
#pragma endregion eAxis
