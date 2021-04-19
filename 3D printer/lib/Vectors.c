#include "Vectors.h"
#include <math.h>

Vector normalizeVector(Vector move){
	return VectorScale(move,1/VectorLength(move));
}

float VectorLength(Vector move){
	return sqrt(pow(move.x,2)+pow(move.y,2)+pow(move.z,2));
}



Vector MultiplayVectors(Vector first,Vector second){
	Vector normie;
	normie.x = first.x*second.x;
	normie.y = first.y*second.y;
	normie.z = first.z*second.z;
	return normie;
}

Vector VectorScale(Vector first, double constant){
	Vector normie;
	normie.x = first.x*constant;
	normie.y = first.y*constant;
	normie.z = first.z*constant;
	return normie;
}

Vector VectorInverse(Vector first){
	Vector normie;
	normie.x = 1/first.x;
	normie.y = 1/first.y;
	normie.z = 1/first.z;
	return normie;
}

Vector VectorDivideVector(Vector first,Vector second){
	Vector normie;
	normie.x = first.x/second.x;
	normie.y = first.y/second.y;
	normie.z = first.z/second.z;
	return normie;
}

Vector DivideConstantVector(int constant,Vector first){
	Vector normie;
	normie.x = constant/first.x;
	normie.y = constant/first.y;
	normie.z = constant/first.z;
	return normie;
}

Vector ONLYPOSITIVEVECTOR(Vector norm){
	Vector normie;
	normie.x = norm.x >=0 ? norm.x : -norm.x;
	normie.y = norm.y >=0 ? norm.y : -norm.y;
	normie.z = norm.z >=0 ? norm.z : -norm.z;
	return normie;
}