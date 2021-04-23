#include "Vectors.h"
#include <math.h>

float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;
	
	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	
	return y;
}

Vector normalizeVector(Vector move){
	return VectorScale(move,(double)Q_rsqrt(pow(move.x,2)+pow(move.y,2)+pow(move.z,2)));
}

float VectorLength(Vector move){
	return sqrt(pow(move.x,2)+pow(move.y,2)+pow(move.z,2));
}

Vector AddVectors(Vector first,Vector second){
	Vector normie;
	normie.x = first.x+second.x;
	normie.y = first.y+second.y;
	normie.z = first.z+second.z;
	return normie;
}

Vector SubVectors(Vector first,Vector second){
	Vector normie;
	normie.x = first.x-second.x;
	normie.y = first.y-second.y;
	normie.z = first.z-second.z;
	return normie;
}

Vector ReluVectors(Vector first){
	Vector normie;
	normie.x = first.x >= 0 ? first.x : 0;
	normie.y = first.y >= 0 ? first.y : 0;
	normie.z = first.z >= 0 ? first.z : 0;
	return normie;
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