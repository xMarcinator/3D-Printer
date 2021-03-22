/*
 * Vectors.h
 *
 * Created: 18/03/2021 08.44.35
 *  Author: Marc
 */ 


#ifndef VECTORS_H_
#define VECTORS_H_

typedef struct {
	double x, y, z;
} Vector;

Vector normalizeVector(Vector move)

Vector MultiplayVectors(Vector first,Vector second)

Vector VectorScale(Vector first, int constant)

Vector VectorDivideVector(Vector first,Vector second)

Vector DivideConstantVector(int constant,Vector first)

#endif /* VECTORS_H_ */