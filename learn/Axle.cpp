// Axle.cpp: implementation of the Axle class.
//
//////////////////////////////////////////////////////////////////////

#include "Axle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace car 
{

	int Axle::wheelsSize = 9;

	Axle::Axle()
	{

	}

	Axle::~Axle()
	{

	}


	void Axle::addWheel(Wheel * wheel){
		wheels.push_back(*wheel);	//derefernce the pointer and use the value into the vector
	}

	Wheel* Axle::getWheel(int index){
		Wheel * ptr = NULL;
		ptr = &wheels[index];
		return ptr;
	}

}