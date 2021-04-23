/*
 * Vectors.h
 *
 * Created: 18/03/2021 08.44.35
 *  Author: Marc
 */ 


#ifndef VECTORS_H_
#define VECTORS_H_

typedef struct Vector{
	double x, y, z;
} Vector;

Vector normalizeVector(Vector move);

float VectorLength(Vector move);

Vector ReluVectors(Vector first);

Vector AddVectors(Vector first,Vector second);

Vector SubVectors(Vector first,Vector second);

Vector MultiplayVectors(Vector first,Vector second);

Vector VectorScale(Vector first, double constant);

Vector VectorDivideVector(Vector first,Vector second);

Vector VectorDivideConstant(Vector first,double second);

Vector DivideConstantVector(int constant,Vector vec);

Vector ONLYPOSITIVEVECTOR(Vector vec);

#endif /* VECTORS_H_ */