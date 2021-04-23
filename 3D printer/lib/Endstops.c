/*
* Endstops.c
*
* Created: 4/19/2021 1:56:39 PM
*  Author: Marc
*/

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include "utils/millis.h"

unsigned char reachedEnd = 0;

void pendEnstops(){
	reachedEnd = 0;	
	EIMSK = (1<<INT1) | (1<<INT4) | (1<<INT4);
}

bool ReachedEnstops(){
	return reachedEnd == 0b111;
}

void initEndstops(){
	EIMSK |= (1<<INT1) | (1<<INT4) | (1<<INT5); //Tænd for external interupt 1,4,5

	init_millis();
	
	sei();

	//aktiver interrupt på den stigende kant på de externe interrupt;
	EICRA |= (1<<ISC11) | (1<<ISC10);
	EICRB |= (1<<ISC41) | (1<<ISC40) | (1<<ISC51) | (1<<ISC50);
}

bool CheckDebounce(unsigned char stop){
	return false;
	static unsigned long last_interrupt_time[3] = {0,0,0};
	unsigned long interrupt_time = millis();
	unsigned long tmp_last_interrupt_time = last_interrupt_time[stop];
	last_interrupt_time[stop] = interrupt_time;
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	return (interrupt_time-tmp_last_interrupt_time > .5);
}

ISR(INT1_vect){
	if(CheckDebounce(0)){
		reachedEnd |=1<<1;
		TIMSK1 &= ~(1<<OCIE1A);//stop x aksen da den længere må køre
		//TODO: Set x position to 0;
	}
}

ISR(INT4_vect){
	if(CheckDebounce(1)){
		reachedEnd |=1<<1;
		TIMSK3 &= ~(1<<OCIE3A);//stop y aksen da den længere må køre
		//TODO: Set y position to 0;
	}
}

ISR(INT5_vect){
	if(CheckDebounce(2)){
		reachedEnd |=1<<2;
		TIMSK4 &= ~(1<<OCIE4A);//stop z aksen da den længere må køre
		//TODO: Set z position to 0;
	}
}


