/*
 * 3D printer.c
 *
 * Created: 15/03/2021 10.54.34
 * Author : Marc
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lib/Vectors.h"
#include "lib/Commander.h"

int main(void)
{
	//initaliser commander
	initCommander();
	
	//forbered en G1 bevægelse
	Vector toMove;
	toMove.x = -4;
	toMove.y = 2;
	toMove.z = 0;	
	
	//kør G1 kommando
	moveLinear(toMove,10);
	
	//sørg for at arduinoen aldrig slukker
    while (1) {
			    
    }
	
	return 0;
}



