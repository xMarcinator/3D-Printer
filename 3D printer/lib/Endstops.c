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
	//reset variable
	reachedEnd = 0;	
	//t�nd for endstops
	EIMSK = (1<<INT1) | (1<<INT4) | (1<<INT4);
}

bool ReachedEnstops(){
	//tjek om de har ramt
	return reachedEnd == 0b111;
}

void initEndstops(){
	EIMSK |= (1<<INT1) | (1<<INT4) | (1<<INT5); //T�nd for external interupt 1,4,5
	//init millis
	init_millis();
	//t�nd for interrupts
	sei();

	//aktiver interrupt p� den stigende kant p� de externe interrupt;
	EICRA |= (1<<ISC11) | (1<<ISC10);
	EICRB |= (1<<ISC41) | (1<<ISC40) | (1<<ISC51) | (1<<ISC50);
}

//funktion som tjekker som der kan udf�res et ineterupt igen
bool CheckDebounce(unsigned char stop){
	//lav en variabel til til hvert endstop
	static unsigned long last_interrupt_time[3] = {0,0,0};
	//f� tiden
	unsigned long interrupt_time = millis();
	//l�g v�rdien over i en midlertigdig variabel
	unsigned long tmp_last_interrupt_time = last_interrupt_time[stop];
	//f� sidste tid for interuptet
	last_interrupt_time[stop] = interrupt_time;
	// hvis der er kommet et interrupt inden for 500 ms s� returner false
	return (interrupt_time-tmp_last_interrupt_time > .5);
}

ISR(INT1_vect){
	//tjek bounce
	if(CheckDebounce(0)){
		//set den har n�et endstops
		reachedEnd |=1<<1;
		TIMSK1 &= ~(1<<OCIE1A);//stop x aksen da den l�ngere m� k�re
		//TODO: Set x position to 0;
	}
}

ISR(INT4_vect){
	if(CheckDebounce(1)){
		//set den har n�et endstops
		reachedEnd |=1<<1;
		TIMSK3 &= ~(1<<OCIE3A);//stop y aksen da den l�ngere m� k�re
		//TODO: Set y position to 0;
	}
}

ISR(INT5_vect){
	//tjek bounce
	if(CheckDebounce(2)){
		//set den har n�et endstops
		reachedEnd |=1<<2;
		TIMSK4 &= ~(1<<OCIE4A);//stop z aksen da den l�ngere m� k�re
		//TODO: Set z position to 0;
	}
}


