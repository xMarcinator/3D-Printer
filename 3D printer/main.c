/*
 * 3D printer.c
 *
 * Created: 15/03/2021 10.54.34
 * Author : Marc
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdbool.h>
#include <lib/Movement.h>

int main(void)
{
	// CTC
	TCCR1B |= (1 << WGM12);
	// Prescaler 1
	TCCR1B |= 1;
	// Output Compare Match A Interrupt Enable
	TIMSK1 |= (1 << OCIE1A);
		
	sei();
	
	DDRH = 3<<5;
	/* Replace with your application code */
	PORTH = 1<<5;
	
	Vector toMove;
	toMove.x=4.5;
	toMove.y=8;
	toMove.z=0;
	
	
	moveLinear(toMove);
	
    while (1) {}
}
