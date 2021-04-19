/*
 * Commander.c
 *
 * Created: 4/19/2021 11:05:49 AM
 *  Author: Marc
 */ 
#include "Vectors.h"
#include "Movement.h"
#include "Extruder.h"
#include "Endstops.h"

unsigned char speed = 8;

Vector Position;
bool homed;

void initCommander(){
	initMovement();
	initExtruder();
	initEndstops();
}

#pragma region Commands
void moveLinear(Vector norm,unsigned char filament){
	setToMove(ONLYPOSITIVEVECTOR(norm));
	
	//normaliser vektor
	float length = VectorLength(norm)
	norm = VectorScale(norm,1/length);
	
	norm = VectorScale(norm,speed);
	norm = VectorDivideVector(speeds,norm);
	setAxisSpeed(norm);
	
	if(filament > 0){
		setExtruderSpeed(length,speed,filament);
	}

	while(!(TIMSK1&(1<<OCIE1A))&&!(TIMSK3&(1<<OCIE1A))&&!(TIMSK4&(1<<OCIE1A))&&!(TIMSK5&(1<<OCIE1A))){
		
	}
}

void home(){
	speed = 8;
	Vector MaxToHome={-229,-229,-229};
	moveLinear(MaxToHome,0)
	while(!ReachedEnstops()){
		
	}
	MaxToHome = {0,0,0};
	setToMove(MaxToHome);
}
#pragma endregion Commands
