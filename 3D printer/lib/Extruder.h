/*
 * Extruder.h
 *
 * Created: 4/19/2021 12:09:23 PM
 *  Author: Marc
 */ 


#ifndef EXTRUDER_H_
#define EXTRUDER_H_


/*
 * Extruder.c
 *
 * Created: 4/18/2021 2:35:30 PM
 *  Author: Marc
 */ 
#define eRotation 1
#define eSteps 200 
#define eMicro 16
#define eScaler 64
#define eSpeed F_CPU * eRotation /(eSteps*eMicro*eScaler)

void setExtruderSpeed(unsigned char Distance, unsigned char Speed, unsigned char Filament);

void initExtruder();

void setEAxisSpeed(double speed);



#endif /* EXTRUDER_H_ */