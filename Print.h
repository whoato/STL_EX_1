#pragma once
#include "Include.h"

class CPrint
{
private:
	static CPrint* m_pInst;
public:
	static CPrint* GetInst()
	{
		if (m_pInst == NULL)
			m_pInst = new CPrint;
		return m_pInst;
	}
public:
	void SetCursorHandle();
	void SetTextColor(int _index);
	void PrintText(int _ix, int _iy, char* _string, int _color = Èò»ö);
	void PrintText(int _ix, int _iy, int _index, int _color = Èò»ö);
	void gotoxy(int _ix, int _iy);
private:
	CPrint();
public:
	~CPrint();
};

