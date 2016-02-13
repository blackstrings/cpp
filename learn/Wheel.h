// Wheel.h: interface for the Wheel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WHEEL_H__54356423_ED7E_4F25_9253_2E8572181E4C__INCLUDED_)
#define AFX_WHEEL_H__54356423_ED7E_4F25_9253_2E8572181E4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

namespace car {


	class Wheel  
	{
	public:
		Wheel(int size, char color, std::string c);
		Wheel();
		virtual ~Wheel();
		int size;
		char color;
		std::string c;
	};

}

#endif // !defined(AFX_WHEEL_H__54356423_ED7E_4F25_9253_2E8572181E4C__INCLUDED_)
