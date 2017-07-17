#pragma once
#include "GameRoom.h"

class CMainGame
{
private:
	static ErrCode ErrNum;
private:
	CGameRoom GameRoom;
	int iNowIndex;
	DWORD m_dwKey;
public:
	void Initialize();
	void Progress();
	void Render();
	void Release();
public:
	USER CreateNewUser();
	void DeleteUser();
	void BanUsers();
	void ClearRoom();
	void PrintRoom();
	void PrintInfo(USER& tUserInfo);
	void KeyCheck();
	void ErrorLine();
public:
	CMainGame();
	~CMainGame();
};

