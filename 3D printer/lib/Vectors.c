#include "Vectors.h"
#include <math.h>

//hutig invers kvardtratrod
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
//funktion som normalisere en vector
Vector normalizeVector(Vector move){
	//find enhedsvektoren ved at gange den med den inverse kvadratrod til summmen af vektorens komponenter i anden
	return VectorScale(move,(double)Q_rsqrt(pow(move.x,2)+pow(move.y,2)+pow(move.z,2)));
}
//funktion som finder en vectors længde
float VectorLength(Vector move){
	//pothagoros
	return sqrt(pow(move.x,2)+pow(move.y,2)+pow(move.z,2));
}
//funktion som lægger to vektore sammen
Vector AddVectors(Vector first,Vector second){
	//lav en ny vektor til resultatet
	Vector normie;
	//læg de korrespoderende komponenter sammen og set dem til den korrespoderende komponent på resultatet
	normie.x = first.x+second.x;
	normie.y = first.y+second.y;
	normie.z = first.z+second.z;
	return normie;
}
//funktion som trækker to vektore fra hinanden 
Vector SubVectors(Vector first,Vector second){
	Vector normie;
	normie.x = first.x-second.x;
	normie.y = first.y-second.y;
	normie.z = first.z-second.z;
	return normie;
}
//funktion som kun returnere en vektor med den positve komponenter
Vector ReluVectors(Vector first){
	Vector normie;
	normie.x = first.x >= 0 ? first.x : 0;
	normie.y = first.y >= 0 ? first.y : 0;
	normie.z = first.z >= 0 ? first.z : 0;
	return normie;
}
//funktion som ganger to vektore sammen
Vector MultiplayVectors(Vector first,Vector second){
	Vector normie;
	normie.x = first.x*second.x;
	normie.y = first.y*second.y;
	normie.z = first.z*second.z;
	return normie;
}

//funktion som ganger en vektor med en konstant
Vector VectorScale(Vector first, double constant){
	Vector normie;
	normie.x = first.x*constant;
	normie.y = first.y*constant;
	normie.z = first.z*constant;
	return normie;
}
//funktion som laver alle vektorens komponter inverse
Vector VectorInverse(Vector first){
	Vector normie;
	normie.x = 1/first.x;
	normie.y = 1/first.y;
	normie.z = 1/first.z;
	return normie;
}

//funktion som dividere de korrepoderende komponenter med hinanden
Vector VectorDivideVector(Vector first,Vector second){
	Vector normie;
	normie.x = first.x/second.x;
	normie.y = first.y/second.y;
	normie.z = first.z/second.z;
	return normie;
}
//en funktion som dividere en konstant med en vektors komponenter
Vector DivideConstantVector(int constant,Vector first){
	Vector normie;
	normie.x = constant/first.x;
	normie.y = constant/first.y;
	normie.z = constant/first.z;
	return normie;
}

//funktion som gør alle komponenter af en vektor positiv
Vector ONLYPOSITIVEVECTOR(Vector norm){
	Vector normie;
	normie.x = norm.x >=0 ? norm.x : -norm.x;
	normie.y = norm.y >=0 ? norm.y : -norm.y;
	normie.z = norm.z >=0 ? norm.z : -norm.z;
	return normie;
}