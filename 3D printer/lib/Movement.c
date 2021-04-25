

#define prescaler 0b11;

#include "Vectors.h"
#include <avr/io.h>
#include <avr/interrupt.h>

Vector ToMove;
Vector MoveCounter;

#pragma region interrupts

#pragma endregion interrupts

void enableSteppers(){
	DDRK = 0b1111<<4; // tænd for steppersne ved at trække enable pins i nul.	
}

#pragma region xAxis
#define XDIR 0
#define XSTEP 2	

void initXAxis(){
	// CTC
	TCCR1B |= (1 << WGM12);
	// set prescaleren
	TCCR1B |= prescaler;
	// slå Output Compare Match interupt til
	TIMSK1 |= (1 << OCIE1A);
	//set stepperens dir og step pins som output på arduinoen
	DDRA |= (1<<XDIR) | (1<<XSTEP);
	//set dir pinen til høj som standard
	PORTA |= (1<<XDIR);
}

ISR(TIMER1_COMPA_vect)
{
	//flip step pinen
	PORTA ^= (1<<XSTEP);
	//tæl kun ned på positionen hvis det er der er gået en hel puls.
	if(PORTA & (1<<XSTEP)){
		//træk ændringen i positionen fra.
		ToMove.x -= 0.00125;
		//tjek som man er tæt nok på den ønskede position
		if(ToMove.x <= 0.000625){
			TIMSK1 &= ~(1<<OCIE1A); //stop interupt
		}
	}
}

void setXAxisSpeed(double speed){
	//tjek om der ingen bevægelse er
	if(speed != 0){
		//lav hastigheden kun positiv og konverter unsigned short
		OCR1A = (unsigned short)(speed<0 ? -1*speed : speed);
		//find ud af om dir skal være høj eller lav
		unsigned char bit = (speed<0);
		//set bitten ud at røre ved andre bits
		PORTA = (PORTA&(~(1&(~bit))<<XDIR)) | bit<<XDIR;
		//tænd for timeren
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
	// set prescaleren
	TCCR3B |= prescaler;
	// slå Output Compare Match interupt til
	TIMSK3 |= (1 << OCIE3A);
	//set stepperens dir og step pins som output på arduinoen
	DDRA |= (1<<YDIR) | (1<<YSTEP);
	//set dir pinen til høj som standard
	PORTA |= 1<<YDIR;
}

ISR(TIMER3_COMPA_vect)	
{
	//flip step pinen
	PORTA ^= (1<<YSTEP);
	//tæl kun ned på positionen hvis det er der er gået en hel puls.
	if(PORTA & (1<<YSTEP)){
		//træk ændringen i positionen fra.
		ToMove.y -= 0.00125;
		//tjek som man er tæt nok på den ønskede position
		if(ToMove.y <= 0.000625){
			TIMSK3 &= ~(1<<OCIE3A); //stop interupt
		}
	}
}

void setYAxisSpeed(double speed){
	//tjek om der ingen bevægelse er
	if(speed != 0){
		//lav hastigheden kun positiv og konverter unsigned short
		OCR3A = (unsigned short)(speed<0 ? -1*speed : speed);
		//find ud af om dir skal være høj eller lav
		unsigned char bit = (speed<0);
		//set bitten ud at røre ved andre bits
		PORTA = (PORTA&(~(1&(~bit))<<YDIR)) | bit<<YDIR;
		//tænd for timeren
		TIMSK3 |= (1<<OCIE3A);
	}	
}
#pragma endregion yAxis

#pragma region zAxis
#define ZDIR 7
#define ZSTEP 5

void initZAxis(){
	// CTC
	TCCR4B |= (1 << WGM42);
	// set prescaleren
	TCCR4B |= prescaler;
	// slå Output Compare Match interupt til
	TIMSK4 |= (1 << OCIE4A);
	//set stepperens dir og step pins som output på arduinoen
	DDRC |= (1<<ZDIR) | (1<<ZSTEP);
	//set dir pinen til høj som standard
	PORTC |= 1<<ZDIR;
}

ISR(TIMER4_COMPA_vect)
{
	//flip step pinen
	PORTC ^= (1<<ZSTEP);
	//tæl kun ned på positionen hvis det er der er gået en hel puls.
	if(PORTC & (1<<ZSTEP)){
		//træk ændringen i positionen fra.
		ToMove.z -= 0.00125;
		//tjek som man er tæt nok på den ønskede position
		if(ToMove.z <= 0.000625){
			TIMSK4 &= ~(1<<OCIE4A); //stop interupt
		}
	}
}

void setZAxisSpeed(double speed){
	//tjek om der ingen bevægelse er
	if(speed != 0){
		//lav hastigheden kun positiv og konverter unsigned short
		OCR4C = (unsigned short)(speed<0 ? -1*speed : speed);
		//find ud af om dir skal være høj eller lav
		unsigned char bit = (speed<0);
		//set bitten ud at røre ved andre bits
		PORTC = (PORTC&(~(1&(~bit))<<ZDIR)) | bit<<ZDIR;
		//tænd for timeren
		TIMSK4 |= (1<<OCIE4A);
	}	
}
#pragma endregion zAxis

//void setAxisSpeed2(unsigned char target,double speed){
	//unsigned char* OCR;
	//unsigned char* PORT;
	//unsigned char* TIMSK;
	//unsigned char DIR;
	//
	//switch (target)
	//{
		//case 4:{
			//OCR = &OCR5C;
			//PORT = &PORTB;
			//TIMSK = &TIMSK4;
			//DIR = ZDIR;
		//}
	//}
	//
	//OCR = (unsigned char)speed;
	//
	//unsigned char bit = (speed<0);
	//
	//PORT = (*PORT&(~(1&(~bit))<<DIR)) | bit<<DIR;
	//
	//TIMSK = *TIMSK|(1<<OCIE1A);
//}

#pragma region axis
//funktion som setter hastighederne på akserne
void setAxisSpeed(Vector speed){
	setXAxisSpeed(speed.x);
	setYAxisSpeed(speed.y);
	setZAxisSpeed(speed.z);
}
#pragma endregion axis

#pragma region Globals
void initMovement(){
	//slå interrputs til
	sei();
	//initaliser akserne
	initXAxis();
	initYAxis();
	initZAxis();
	//tænd på steppers
	enableSteppers();
}
//funktion som sætter hvor meget den skal køre
void setToMove(Vector movement){
	ToMove = movement;
}


#pragma endregion Globals

