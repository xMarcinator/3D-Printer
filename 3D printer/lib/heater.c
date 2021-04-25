/*
 * heater.c
 *
 * Created: 4/21/2021 2:38:53 PM
 *  Author: Marc
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>


unsigned char dutyCycle[2];
void initHeater(){
	//
	TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20) | (1 << WGM21); // set mode til pwm og sla OC1A og OC1B til
	TCCR2B = (1 << CS00) | (1 << CS02); // set prescaler
	TIMSK2 = (1 << TOIE0); //enable timer interrupt
	
	OCR2A = dutyCycle[0]*2.55;//set duty cycle
	OCR2B = dutyCycle[1]*2.55;//set duty cycle
}

ISR(TIMER0_OVF_vect)
{
	
}
