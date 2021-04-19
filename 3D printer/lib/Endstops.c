/*
 * Endstops.c
 *
 * Created: 4/19/2021 1:56:39 PM
 *  Author: Marc
 */ 
#include "avr\iom2560.h"

unsigned char reachedEnd = 0;

void pendEnstops(){
	reachedEnd = 0;
	EIMSK |= 1<<INT1 | 1<<INT5 | 1<<INT6;
}

bool ReachedEnstops(){
	return reachedEnd == 0b111;
}

void initEndstops(){
	EICRA |= 1<<ISC11;
	EICRB |= 1<<ISC51 | 1<<ISC61;
}

ISR(INT1_vect){
	reachedEnd |=1<<0;
	TIMSK1 &= ~(1<<OCIE1A);
	if (reachedEnd == 0b111) EIMSK &= ~(1<<INT1 | 1<<INT5 | 1<<INT6);
}
ISR(INT5_vect){
	reachedEnd |=1<<1;
	TIMSK3 &= ~(1<<OCIE3A);
	if (reachedEnd == 0b111) EIMSK &= ~(1<<INT1 | 1<<INT5 | 1<<INT6);
}
ISR(INT6_vect){
	reachedEnd |=1<<2;
	TIMSK4 &= ~(1<<OCIE4A);
	if (reachedEnd == 0b111) EIMSK &= ~(1<<INT1 | 1<<INT5 | 1<<INT6);
}
