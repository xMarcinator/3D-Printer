/*
 * Endstops.h
 *
 * Created: 4/19/2021 2:41:08 PM
 *  Author: Marc
 */ 


#ifndef ENDSTOPS_H_
#define ENDSTOPS_H_
#include <stdbool.h>

void pendEnstops();

bool ReachedEnstops();

void initEndstops();


#endif /* ENDSTOPS_H_ */