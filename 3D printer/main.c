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
	
	//forbered en G1 bev�gelse
	Vector toMove;
	toMove.x = -4;
	toMove.y = 2;
	toMove.z = 0;	
	
	//k�r G1 kommando
	moveLinear(toMove,10);
	
	//s�rg for at arduinoen aldrig slukker
    while (1) {
			    
    }
	
	return 0;
}



