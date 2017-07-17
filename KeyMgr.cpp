#pragma once
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInst = NULL;

CKeyMgr::CKeyMgr()
{
}


CKeyMgr::~CKeyMgr()
{
}


void CKeyMgr::CheckKey()
{
	m_dwKey = 0;

	if (GetAsyncKeyState(0x41) & 0x8000)	//A
	{
		m_dwKey |= KEY_A;
	}
	if (GetAsyncKeyState(0x53) & 0x8000)	//S	
	{
		m_dwKey |= KEY_S;
	}
	if (GetAsyncKeyState(0x44) & 0x8000)	//D
	{
		m_dwKey |= KEY_D;
	}
	if (GetAsyncKeyState(0x46) & 0x8000)	//F
	{
		m_dwKey |= KEY_F;
	}
	if (GetAsyncKeyState(0x47) & 0x8000)	// G
	{
		m_dwKey |= KEY_G;
	}
	if (GetAsyncKeyState(0x59) & 0x8000)	//Y
	{
		m_dwKey |= KEY_Y;
	}
	if (GetAsyncKeyState(0x4E) & 0x8000)	//N
	{
		m_dwKey |= KEY_N;
	}
	if ((GetAsyncKeyState(0x31) & 0x8000) || (GetAsyncKeyState(VK_NUMPAD1) & 0x8000))
	{ 
		m_dwKey |= KEY_1;
	}
	if ((GetAsyncKeyState(0x32) & 0x8000) || (GetAsyncKeyState(VK_NUMPAD2) & 0x8000))
	{
		m_dwKey |= KEY_2;
	}
	if ((GetAsyncKeyState(0x33) & 0x8000) || (GetAsyncKeyState(VK_NUMPAD3) & 0x8000))
	{
		m_dwKey |= KEY_3;
	}
	if ((GetAsyncKeyState(0x34) & 0x8000) || (GetAsyncKeyState(VK_NUMPAD4) & 0x8000))
	{
		m_dwKey |= KEY_4;
	}
	if ((GetAsyncKeyState(0x35) & 0x8000) || (GetAsyncKeyState(VK_NUMPAD5) & 0x8000))
	{
		m_dwKey |= KEY_5;
	}
	if ((GetAsyncKeyState(0x36) & 0x8000) || (GetAsyncKeyState(VK_NUMPAD6) & 0x8000))
	{
		m_dwKey |= KEY_6;
	}
}
