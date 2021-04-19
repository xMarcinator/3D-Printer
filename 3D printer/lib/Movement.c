#define xSpeed 20000;
#define ySpeed 20000;
#define zSpeed 20000;
#define eSpeed 20000;

#define prescaler 0b11;

#include "Vectors.h"
#include <avr/io.h>
#include <avr/interrupt.h>

const int speed = 2000;

Vector ToMove;
Vector MoveCounter;
Vector speeds;

#pragma region interrupts

#pragma endregion interrupts

void enableSteppers(){
	DDRD |= 1<<7; //x stepper enable
	DDRF |= 1<<2; //y stepper enable
	DDRF |= 1<<8; //z stepper enable
	DDRA |= 1<<2; //e stepper enable
}

#pragma region xAxis
#define XDIR 1
#define XSTEP 0	

void initXAxis(){
	// CTC
	TCCR1B |= (1 << WGM12);
	// Prescaler 1
	TCCR1B |= prescaler;
	// Output Compare Match A Interrupt Enable
	TIMSK1 |= (1 << OCIE1A);
	
	DDRF |= (1<<XDIR) | (1<<XSTEP);
	/* Replace with your application code */
	PORTF |= (1<<XDIR);
}

ISR(TIMER1_COMPA_vect)
{
	PORTF ^= (1<<XSTEP);
	
	if(PORTF & (1<<XSTEP)){
		ToMove.x -= 0.00125;
		if(ToMove.x <= 0.000625){
			TIMSK1 &= ~(1<<OCIE1A); //stop interupt
		}
	}
}

void setXAxisSpeed(double speed){
	OCR1A = (unsigned char) speed;
	
	unsigned char bit = (speed<0);

	PORTF = (PORTF&(~(1&(~bit))<<XDIR)) | bit<<XDIR;
	
	TIMSK1 |= (1<<OCIE1A);
}
#pragma endregion xAxis

#pragma region yAxis
#define YDIR 7
#define YSTEP 6

void initYAxis(){
	// CTC
	TCCR3B |= (1 << WGM32);
	// Prescaler 1
	TCCR3B |= prescaler;
	// Output Compare Match A Interrupt Enable
	TIMSK3 |= (1 << OCIE3A);
	
	DDRF |= (1<<YDIR) | (1<<YSTEP);
	/* Replace with your application code */
	PORTF |= 1<<YDIR;
}

ISR(TIMER3_COMPA_vect)
{
	PORTF ^= (1<<YSTEP);
	
	if(PORTF & (1<<YSTEP)){
		ToMove.x -= 0.00125;
		if(ToMove.x <= 0.000625){
			TIMSK3 &= ~(1<<OCIE3A); //stop interupt
		}
	}
}

void setYAxisSpeed(double speed){
	OCR3A = speed;
	
	unsigned char bit = (speed<0);

	PORTA = (PORTA&(~(1&(~bit))<<YDIR)) | bit<<YDIR;
	
	TIMSK3 |= (1<<OCIE3A);
}
#pragma endregion yAxis

#pragma region zAxis
#define ZDIR 3
#define ZSTEP 1	

void initZAxis(){
	// CTC
	TCCR4B |= (1 << WGM42);
	// Prescaler 1
	TCCR4B |= prescaler;
	// Output Compare Match A Interrupt Enable
	TIMSK4 |= (1 << OCIE4A);
	
	DDRL |= (1<<ZDIR) | (1<<ZSTEP);
	/* Replace with your application code */
	PORTL |= 1<<ZDIR;
}

ISR(TIMER4_COMPA_vect)
{
	PORTL ^= (1<<ZSTEP);
	
	if(PORTL & (1<<ZSTEP)){
		ToMove.x -= 0.00125;
		if(ToMove.x <= 0.000625){
			TIMSK4 &= ~(1<<OCIE4A); //stop interupt
		}
	}
}

void setZAxisSpeed(double speed){
	OCR4C = speed;
	
	unsigned char bit = (speed<0);
		
	PORTL = (PORTL&(~(1&(~bit))<<ZDIR)) | bit<<ZDIR;
	
	TIMSK4 |= (1<<OCIE4A);
}
#pragma endregion zAxis

void setAxisSpeed(unsigned char target,double speed){
	uint8_t* OCR;
	uint8_t* PORT;
	uint8_t* TIMSK;
	unsigned char DIR;
	
	switch (target)
	{
		case 4:{
			OCR = &OCR5C
			PORT = &PORTB
			TIMSK = &TIMSK4
			DIR = ZDIR;
		}
	}
	
	OCR = speed;
	
	unsigned char bit = (speed<0);
	
	PORT = (PORT&(~(1&(~bit))<<DIR)) | bit<<DIR;
	
	TIMSK |= (1<<OCIE1A);
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
	speeds.x = xSpeed;
	speeds.y = ySpeed;
	speeds.z = zSpeed;
	
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

