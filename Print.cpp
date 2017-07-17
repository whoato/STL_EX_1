#include "Print.h"

CPrint* CPrint::m_pInst = NULL;

CPrint::CPrint()
{
}


CPrint::~CPrint()
{
}


void CPrint::SetCursorHandle()
{
	HANDLE HCursor = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Info;
	Info.dwSize = 100;
	Info.bVisible = FALSE;
	SetConsoleCursorInfo(HCursor, &Info);
}

void CPrint::SetTextColor(int _index)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _index);
}

void CPrint::PrintText(int _ix, int _iy, char* _string, int _color)
{
	DWORD dw;
	COORD CursorPosition;

	CursorPosition.X = _ix;
	CursorPosition.Y = _iy;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
	SetTextColor(_color);
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), _string, strlen(_string), &dw, NULL);
}

void CPrint::PrintText(int _ix, int _iy, int _index, int _color)
{
	DWORD dw;
	COORD CursorPosition;

	CursorPosition.X = _ix;
	CursorPosition.Y = _iy;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
	SetTextColor(_color);

	char str[128];
	char* pstr = itoa(_index, str, 10);
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), pstr, strlen(pstr), &dw, NULL);
}

void CPrint::gotoxy(int _ix, int _iy)
{
	COORD CursorPosition;

	CursorPosition.X = _ix;
	CursorPosition.Y = _iy;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}