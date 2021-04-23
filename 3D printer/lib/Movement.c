

#define prescaler 0b11;

#include "Vectors.h"
#include <avr/io.h>
#include <avr/interrupt.h>

Vector ToMove;
Vector MoveCounter;

#pragma region interrupts

#pragma endregion interrupts

void enableSteppers(){
	/*DDRD |= 1<<7; //x stepper enable
	DDRF |= 1<<2; //y stepper enable
	DDRF |= 1<<8; //z stepper enable
	DDRA |= 1<<2; //e stepper enable*/
	DDRK = 0b1111<<4; // træk enable pins i nul.	
}

#pragma region xAxis
#define XDIR 0
#define XSTEP 2	

void initXAxis(){
	// CTC
	TCCR1B |= (1 << WGM12);
	// Prescaler 1
	TCCR1B |= prescaler;
	// Output Compare Match A Interrupt Enable
	TIMSK1 |= (1 << OCIE1A);
	
	DDRA |= (1<<XDIR) | (1<<XSTEP);
	/* Replace with your application code */
	PORTA |= (1<<XDIR);
}

ISR(TIMER1_COMPA_vect)
{
	PORTA ^= (1<<XSTEP);
	
	if(PORTA & (1<<XSTEP)){
		ToMove.x -= 0.00125;
		if(ToMove.x <= 0.000625){
			TIMSK1 &= ~(1<<OCIE1A); //stop interupt
		}
	}
}

void setXAxisSpeed(double speed){
	if(speed != 0){
		OCR1A = (unsigned short)(speed<0 ? -1*speed : speed);
		
		unsigned char bit = 0;

		PORTA = (PORTA&(~(1&(~bit))<<XDIR)) | bit<<XDIR;
		//PORTF = (PORTF & (~(1<<XDIR))) | bit<<XDIR;
	
		TIMSK1 |= (1<<OCIE1A);
	}
}
#pragma endregion xAxis

#pragma region yAxis
#define YDIR 4
#define YSTEP 6

void initYAxis(){
	// CTC
	TCCR3B |= (1 << WGM32);
	// Prescaler 1
	TCCR3B |= prescaler;
	// Output Compare Match A Interrupt Enable
	TIMSK3 |= (1 << OCIE3A);
	
	DDRA |= (1<<YDIR) | (1<<YSTEP);
	/* Replace with your application code */
	PORTA |= 1<<YDIR;
}

ISR(TIMER3_COMPA_vect)	
{
	PORTA ^= (1<<YSTEP);
	
	if(PORTA & (1<<YSTEP)){
		ToMove.y -= 0.00125;
		if(ToMove.y <= 0.000625){
			TIMSK3 &= ~(1<<OCIE3A); //stop interupt
		}
	}
}

void setYAxisSpeed(double speed){
	OCR3A = (unsigned short)(speed<0 ? -1*speed : speed);
	
	unsigned char bit = (speed<0);

	PORTA = (PORTA&(~(1&(~bit))<<YDIR)) | bit<<YDIR;
	
	TIMSK3 |= (1<<OCIE3A);
}
#pragma endregion yAxis

#pragma region zAxis
#define ZDIR 7
#define ZSTEP 5

void initZAxis(){
	// CTC
	TCCR4B |= (1 << WGM42);
	// Prescaler 1
	TCCR4B |= prescaler;
	// Output Compare Match A Interrupt Enable
	TIMSK4 |= (1 << OCIE4A);
	
	DDRC |= (1<<ZDIR) | (1<<ZSTEP);
	/* Replace with your application code */
	PORTC |= 1<<ZDIR;
}

ISR(TIMER4_COMPA_vect)
{
	PORTC ^= (1<<ZSTEP);
	
	if(PORTC & (1<<ZSTEP)){
		ToMove.z -= 0.00125;
		if(ToMove.z <= 0.000625){
			TIMSK4 &= ~(1<<OCIE4A); //stop interupt
		}
	}
}

void setZAxisSpeed(double speed){
	OCR4C = (unsigned short)(speed<0 ? -1*speed : speed);
	
	unsigned char bit = (speed<0);
		
	PORTC = (PORTC&(~(1&(~bit))<<ZDIR)) | bit<<ZDIR;
	
	TIMSK4 |= (1<<OCIE4A);
}
#pragma endregion zAxis

void setAxisSpeed2(unsigned char target,double speed){
	unsigned char* OCR;
	unsigned char* PORT;
	unsigned char* TIMSK;
	unsigned char DIR;
	
	switch (target)
	{
		case 4:{
			OCR = &OCR5C;
			PORT = &PORTB;
			TIMSK = &TIMSK4;
			DIR = ZDIR;
		}
	}
	
	OCR = (unsigned char)speed;
	
	unsigned char bit = (speed<0);
	
	PORT = (*PORT&(~(1&(~bit))<<DIR)) | bit<<DIR;
	
	TIMSK = *TIMSK|(1<<OCIE1A);
}

#pragma region axis
void setAxisSpeed(Vector speed){
	setXAxisSpeed(speed.x);
	setYAxisSpeed(speed.y);
	setZAxisSpeed(speed.z);
}
#pragma endregion axis

#pragma region Globals
void initMovement(){
	sei();
	initXAxis();
	initYAxis();
	initZAxis();
	
	enableSteppers();
}

void setToMove(Vector movement){
	ToMove = movement;
}


#pragma endregion Globals

