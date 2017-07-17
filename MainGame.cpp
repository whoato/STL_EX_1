#pragma once
#include "MainGame.h"
#include "KeyMgr.h"

ErrCode CMainGame::ErrNum = ERR_FINE;

CMainGame::CMainGame()
	:iNowIndex(0)
{
}


CMainGame::~CMainGame()
{
}


void CMainGame::Initialize()
{
	CPrint::GetInst()->SetCursorHandle();

}
void CMainGame::Progress()	
{
	CKeyMgr::GetInst()->CheckKey();
	KeyCheck();
	if (GameRoom.IsEmpty())
	{
		iNowIndex = EMPTY;
	}
}
void CMainGame::Render()	
{
	PrintRoom();

	switch (iNowIndex)
	{
	case MASTER:
		PrintInfo(GameRoom.GetMasterUser());
		break;
	case LAST:
		PrintInfo(GameRoom.GetLastUserInfo());
		break;
	case EMPTY:
		ErrNum = SYS_EMPTY;
		break;
	default:
		PrintInfo(GameRoom.GetUserInfo(iNowIndex));
	}
	
	ErrorLine();
}
void CMainGame::Release()	
{

}

USER CMainGame::CreateNewUser()
{
	USER User(10, 100);

	char buffer[100];
	cout << "추가할 이름을 입력하세요" << endl;
	cin.clear();
	cin >> buffer;

	User.username = new char[strlen(buffer)];
	strcpy(User.username, buffer);

	return User;
}

void CMainGame::PrintRoom()
{
	char* str = "현재 유저 수 : ";
	CPrint::GetInst()->PrintText(0, 1, str, 연한빨간색);
	CPrint::GetInst()->PrintText(strlen(str), 1, GameRoom.ReturnSize());
	CPrint::GetInst()->PrintText(strlen(str) + 2, 1, "/ 6");
	
	str = "유저 삭제 = 'A', 유저 추가 = 'S', 유저 퇴출 = 'D', 모든 유저 삭제 = 'F'";
	CPrint::GetInst()->PrintText(0, 2, str);
	str = "방장 정보 확인 = '1', 유저 정보 확인 = '1 ~ 6', 마지막에 들어온 유저 정보 확인 = 'G'";
	CPrint::GetInst()->PrintText(0, 3, str);

	str = "▽유저 목록 (유저 이름)";
	CPrint::GetInst()->PrintText(0, 4, str, 진한흰색);
	
	if (!GameRoom.IsEmpty())
	{
		for (int i = 0; i < GameRoom.ReturnSize(); i++)
			CPrint::GetInst()->PrintText(0, 5 + i, GameRoom.GetUserInfo(i).username);
	}
	else
	{
		ErrNum = SYS_EMPTY;
	}
}

void CMainGame::PrintInfo(USER& tUserInfo)
{
	int ix = 0; 
	int iy = 12;
	char* str = "유저 정보";
	CPrint::GetInst()->PrintText(ix, iy, str);
	
	str = "유저 이름 : ";
	CPrint::GetInst()->PrintText(ix, iy + 1, str);
	CPrint::GetInst()->PrintText(ix + strlen(str), iy + 1, tUserInfo.username, 진한흰색);

	str = "유저 레벨 : ";
	CPrint::GetInst()->PrintText(ix, iy + 2, str);
	CPrint::GetInst()->PrintText(ix + strlen(str), iy + 2, tUserInfo.level, 연한파란색);

	str = "유저 경험치 : ";
	CPrint::GetInst()->PrintText(ix, iy + 3, str);
	CPrint::GetInst()->PrintText(ix + strlen(str), iy + 3, tUserInfo.exp, 연한노란색);
}

void CMainGame::KeyCheck()
{
	m_dwKey = CKeyMgr::GetInst()->GetKey();

	if (!GameRoom.IsEmpty())
	{
		if (m_dwKey & KEY_A)
		{
			char bufDel[100];
			cout << "삭제할 이름을 입력하세요" << endl;
			cin >> bufDel;

			ErrNum = GameRoom.DelUser(bufDel);
		}
		if (m_dwKey & KEY_D)
		{
			int num = 0;
			cout << "1~6까지의 숫자를 입력하세요." << endl;
			cin >> num;

			if (cin.fail())
			{
				ErrNum = ERR_WR_NUM;
			}
			else
			{
				num--;
				ErrNum = GameRoom.BanUser(num);
			}
		}
	}
	
	if (m_dwKey & KEY_S)
	{
		iNowIndex = MASTER;
		ErrNum = GameRoom.AddUser(CreateNewUser());
		
	}
	if (m_dwKey & KEY_F)
	{
		char bufClr[100];
		cout << "정말로 삭제할까요? Y / N" << endl;
		cin >> bufClr;
		if (!strcmp(bufClr, "y") || !strcmp(bufClr, "Y"))
		{
			GameRoom.Clear();
		}
		else if (!strcmp(bufClr, "n") || !strcmp(bufClr, "N"))
		{
			ErrNum = ERR_FINE;
		}
		else
		{
			ErrNum = ERR_WR_STR;
		}
	}
	if (m_dwKey & KEY_G)
	{
		iNowIndex = LAST;
	}
	if (m_dwKey & KEY_1)
	{
		iNowIndex = MASTER;
	}
	if (m_dwKey & KEY_2)
	{
		iNowIndex = 1;
	}
	if (m_dwKey & KEY_3)
	{
		iNowIndex = 2;
	}
	if (m_dwKey & KEY_4)
	{
		iNowIndex = 3;
	}
	if (m_dwKey & KEY_5)
	{
		iNowIndex = 4;
	}
	if (m_dwKey & KEY_6)
	{
		iNowIndex = 5;
	}
}

void CMainGame::ErrorLine()
{
	switch (ErrNum)
	{
	case ERR_ISFULL:
		CPrint::GetInst()->PrintText(0, 18, "ERROR_ :: 방이 가득 찼습니다.");
		break;
	case ERR_NO_PL:
		CPrint::GetInst()->PrintText(0, 18, "ERROR_ :: 지정한 유저가 없습니다.");
		break;
	case SYS_DEL_MS:
		CPrint::GetInst()->PrintText(0, 19, "SYSTEM :: 방장이 ");
		CPrint::GetInst()->PrintText(18, 19, GameRoom.GetUserInfo(0).username);
		CPrint::GetInst()->PrintText(18 + strlen(GameRoom.GetUserInfo(0).username), 19, " 님으로 변경되었습니다.");
	case SYS_DEL_PL:
		CPrint::GetInst()->PrintText(0, 18, "SYSTEM :: 지정 유저가 삭제되었습니다.");
		break;
	case ERR_WR_NUM:
		CPrint::GetInst()->PrintText(0, 18, "ERROR_ :: 틀린 번호입니다.");
		break;
	case ERR_WR_STR:
		CPrint::GetInst()->PrintText(0, 18, "ERROR_ :: Y 또는 N을 입력하세요.");
		break;
	case SYS_EMPTY:
		CPrint::GetInst()->PrintText(0, 18, "ERROR_ :: 방이 비어있습니다.");
		break;
	case ERR_FINE:
		CPrint::GetInst()->PrintText(0, 18, "...");
	default:
		ErrNum = ERR_FINE;
		break;
	}
}