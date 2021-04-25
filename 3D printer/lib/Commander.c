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
#include "heater.h"
#include "Commander.h"

unsigned char speed = 100;

Vector Position;
Vector speeds;
bool homed;

//function som initalisere alle komponenter
void initCommander(){
	//set sammenhæng mellem hastighed på timercount
	speeds.x = xTiming;
	speeds.y = yTiming;
	speeds.z = zTiming;
	
	//inilisere de andre komponenter
	initMovement();
	initExtruder();
	initEndstops();
	initHeater();
}

Vector preventOutOfBounds(Vector Pos){
	//find ud af hvad positionen efter denne kommando vil være;
	Vector outOfBound = AddVectors(Position,Pos);
	//sørg for at kommandoen ikke bevæger sig længere end den kan.
	if(outOfBound.x>depth) Pos.x = depth - Position.x;
	if(outOfBound.y>height) Pos.y = height - Position.y;
	if(outOfBound.z>width) Pos.z = width - Position.z;
	
	if(outOfBound.x<0) Pos.x = -Position.x;
	if(outOfBound.y<0) Pos.y = -Position.y;
	if(outOfBound.z<0) Pos.z = -Position.z;
}

#pragma region Commands
//funktion som får printeren til at bevæge sig i en lige linje og extruder så meget filament.
void moveLinear(Vector norm,unsigned char filament){
	//Tilaps kommandoen så den ikke går ud over print området.
	norm = preventOutOfBounds(norm);
	//set den nye position til memory.
	Position = AddVectors(Position,norm);
	//set den variabel som bestemmer hvor langtid at timerne skal køre. (Timerne tælle altid ned, derfor skal alle værdier være positive)
	setToMove(ONLYPOSITIVEVECTOR(norm));
	
	//normaliser vektor
	norm = normalizeVector(norm);
	//gang vektoren ved den  ønskede hastighed
	norm = VectorScale(norm,speed);
	//lave hastigheden om til en timercount
	norm = VectorDivideVector(speeds,norm);
	//set timernes counter
	setAxisSpeed(norm);
	//set extruderens hastighed hvis det er at den er større end nul
	if(filament > 0){
		setExtruderSpeed(VectorLength(norm),speed,filament);
	}
	//vent på at alle akser er færdige
	while(!(TIMSK1&(1<<OCIE1A))&&!(TIMSK3&(1<<OCIE1A))&&!(TIMSK4&(1<<OCIE1A))&&!(TIMSK5&(1<<OCIE1A))){
		
	}
}
//funktion som får printeren til at køre til 0,0,0
void home(){
	//set hastigheden af printeren
	speed = 8;
	//få printeren til at flytte sig hele printerens flade.
	Vector MaxToHome={-229,-229,-229};
	moveLinear(MaxToHome,0);
	//vent til at den er færdig
	while(!ReachedEnstops()){
		
	}
	//reset timerenes counter til 0
	Vector HomePos = {0,0,0};
	setToMove(HomePos);
}
#pragma endregion Commands
