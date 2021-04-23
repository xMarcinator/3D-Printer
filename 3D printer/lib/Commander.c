/*
 * Commander.c
 *
 * Created: 4/19/2021 11:05:49 AM
 *  Author: Marc
 */ 
#include <stdbool.h>
#include <avr/interrupt.h>
#include "Vectors.h"
#include "Movement.h"
#include "Extruder.h"
#include "Endstops.h"
#include "Commander.h"

unsigned char speed = 100;

Vector Position;
Vector speeds;
bool homed;

void initCommander(){
	speeds.x = xTiming;
	speeds.y = yTiming;
	speeds.z = zTiming;
	
	initMovement();
	//initExtruder();
	//initEndstops();
}

Vector preventOutOfBounds(Vector Pos){
	Vector outOfBound = AddVectors(Position,Pos);
	if(outOfBound.x>depth) Pos.x = depth - Position.x;
	if(outOfBound.y>height) Pos.y = height - Position.y;
	if(outOfBound.z>width) Pos.z = width - Position.z;
	
	if(outOfBound.x<0) Pos.x = -Position.x;
	if(outOfBound.y<0) Pos.y = -Position.y;
	if(outOfBound.z<0) Pos.z = -Position.z;
}

#pragma region Commands
void moveLinear(Vector norm,unsigned char filament){
	//norm = preventOutOfBounds(norm);
	
	Position = AddVectors(Position,norm);
	
	//Vector bar = {100,100,0};
	
	setToMove(ONLYPOSITIVEVECTOR(norm));
	//setToMove(bar);
	
	//normaliser vektor
	norm = normalizeVector(norm);
	
	norm = VectorScale(norm,speed);
	norm = VectorDivideVector(speeds,norm);
	
	setAxisSpeed(norm);
	
	if(filament > 0){
		setExtruderSpeed(VectorLength(norm),speed,filament);
	}

	while(!(TIMSK1&(1<<OCIE1A))&&!(TIMSK3&(1<<OCIE1A))&&!(TIMSK4&(1<<OCIE1A))&&!(TIMSK5&(1<<OCIE1A))){
		
	}
}

void home(){
	speed = 8;
	Vector MaxToHome={-229,-229,-229};
	moveLinear(MaxToHome,0);
	while(!ReachedEnstops()){
		
	}
	Vector HomePos = {0,0,0};
	setToMove(HomePos);
}
#pragma endregion Commands
