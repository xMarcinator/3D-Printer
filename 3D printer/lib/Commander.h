/*
 * Commander.h
 *
 * Created: 4/19/2021 12:30:57 PM
 *  Author: Marc
 */ 


#ifndef COMMANDER_H_
#define COMMANDER_H_

#include "Vectors.h"

#define width 200
#define depth 200
#define height 200

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define stepperSteps 200
#define microsteps 16
#define scaler 64

#define xRotation 4
#define yRotation 4
#define zRotation 4
#define eRotation 4

#define xTiming 2 * F_CPU * xRotation /(stepperSteps*microsteps*scaler)
#define yTiming 2 * F_CPU * yRotation /(stepperSteps*microsteps*scaler)
#define zTiming 2 * F_CPU * zRotation /(stepperSteps*microsteps*scaler)
#define eTiming 2 * F_CPU * eRotation /(stepperSteps*microsteps*scaler)

void moveLinear(Vector norm,unsigned char filament);



#endif /* COMMANDER_H_ */