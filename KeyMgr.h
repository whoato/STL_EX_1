#pragma once
#include "Include.h"

class CKeyMgr
{
private:
	static CKeyMgr* m_pInst;
public:
	static CKeyMgr* GetInst()
	{
		if (m_pInst == NULL)
			m_pInst = new CKeyMgr;
		return m_pInst;
	}
private:
	DWORD m_dwKey;
public:
	DWORD GetKey() { return m_dwKey; }
public:
	void CheckKey();
private:
	CKeyMgr();
public:
	~CKeyMgr();
};

