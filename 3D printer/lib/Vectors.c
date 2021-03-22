#include <Vectors.h>

Vector normalizeVector(Vector move){
	float sq = 1/sqrt(pow(move.x,2)+pow(move.y,2)+pow(move.z,2));
	return MultiplayVectorConstant(move,sq);
}

Vector MultiplayVectors(Vector first,Vector second){
	Vector normie;
	normie.x = first.x*second.x;
	normie.y = first.y*second.y;
	normie.z = first.z*second.z;
	return normie;
}

Vector VectorScale(Vector first, int constant){
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