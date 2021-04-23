/*
 * millis.c
 *
 * Created: 4/21/2021 1:56:32 PM
 *  Author: Marc
 */ 
#include <avr/io.h>
#include <util/atomic.h>
#include <avr/interrupt.h>

volatile unsigned long timer1_millis;
//NOTE: A unsigned long holds values from 0 to 4,294,967,295 (2^32 - 1). It will roll over to 0 after reaching its maximum value.

ISR(TIMER2_COMPA_vect)
{
	timer1_millis++;
}

void init_millis(unsigned long f_cpu)
{
	// (Set timer to clear when matching ctc_match_overflow) | (Set clock divisor to 8)
	TCCR2A |= (1 << WGM21);
	TCCR2B |= (1 << CS22);
	
	// high byte first, then low byte
	OCR2A = 250;
	
	// Enable the compare match interrupt
	TIMSK2 |= (1 << OCIE2A);
	
	//REMEMBER TO ENABLE GLOBAL INTERRUPTS AFTER THIS WITH sei(); !!!
}

unsigned long millis ()
{
	unsigned long millis_return;
	
	// Ensure this cannot be disrupted
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		millis_return = timer1_millis;
	}
	return millis_return;
}