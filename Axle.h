// Axle.h: interface for the Axle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AXLE_H__122A1B67_422B_4939_8384_3B2CE55A5AEF__INCLUDED_)
#define AFX_AXLE_H__122A1B67_422B_4939_8384_3B2CE55A5AEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wheel.h"
#include <vector>

class Axle  
{
public:
	std::vector<Wheel> wheels;
	static int wheelsSize;

	Axle();
	virtual ~Axle();
	void addWheel(Wheel *wheel);
	Wheel* Axle::getWheel(int index);



};

#endif // !defined(AFX_AXLE_H__122A1B67_422B_4939_8384_3B2CE55A5AEF__INCLUDED_)
