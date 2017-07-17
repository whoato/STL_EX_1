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
	cout << "�߰��� �̸��� �Է��ϼ���" << endl;
	cin.clear();
	cin >> buffer;

	User.username = new char[strlen(buffer)];
	strcpy(User.username, buffer);

	return User;
}

void CMainGame::PrintRoom()
{
	char* str = "���� ���� �� : ";
	CPrint::GetInst()->PrintText(0, 1, str, ���ѻ�����);
	CPrint::GetInst()->PrintText(strlen(str), 1, GameRoom.ReturnSize());
	CPrint::GetInst()->PrintText(strlen(str) + 2, 1, "/ 6");
	
	str = "���� ���� = 'A', ���� �߰� = 'S', ���� ���� = 'D', ��� ���� ���� = 'F'";
	CPrint::GetInst()->PrintText(0, 2, str);
	str = "���� ���� Ȯ�� = '1', ���� ���� Ȯ�� = '1 ~ 6', �������� ���� ���� ���� Ȯ�� = 'G'";
	CPrint::GetInst()->PrintText(0, 3, str);

	str = "������ ��� (���� �̸�)";
	CPrint::GetInst()->PrintText(0, 4, str, �������);
	
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
	char* str = "���� ����";
	CPrint::GetInst()->PrintText(ix, iy, str);
	
	str = "���� �̸� : ";
	CPrint::GetInst()->PrintText(ix, iy + 1, str);
	CPrint::GetInst()->PrintText(ix + strlen(str), iy + 1, tUserInfo.username, �������);

	str = "���� ���� : ";
	CPrint::GetInst()->PrintText(ix, iy + 2, str);
	CPrint::GetInst()->PrintText(ix + strlen(str), iy + 2, tUserInfo.level, �����Ķ���);

	str = "���� ����ġ : ";
	CPrint::GetInst()->PrintText(ix, iy + 3, str);
	CPrint::GetInst()->PrintText(ix + strlen(str), iy + 3, tUserInfo.exp, ���ѳ����);
}

void CMainGame::KeyCheck()
{
	m_dwKey = CKeyMgr::GetInst()->GetKey();

	if (!GameRoom.IsEmpty())
	{
		if (m_dwKey & KEY_A)
		{
			char bufDel[100];
			cout << "������ �̸��� �Է��ϼ���" << endl;
			cin >> bufDel;

			ErrNum = GameRoom.DelUser(bufDel);
		}
		if (m_dwKey & KEY_D)
		{
			int num = 0;
			cout << "1~6������ ���ڸ� �Է��ϼ���." << endl;
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
		cout << "������ �����ұ��? Y / N" << endl;
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
		CPrint::GetInst()->PrintText(0, 18, "ERROR_ :: ���� ���� á���ϴ�.");
		break;
	case ERR_NO_PL:
		CPrint::GetInst()->PrintText(0, 18, "ERROR_ :: ������ ������ �����ϴ�.");
		break;
	case SYS_DEL_MS:
		CPrint::GetInst()->PrintText(0, 19, "SYSTEM :: ������ ");
		CPrint::GetInst()->PrintText(18, 19, GameRoom.GetUserInfo(0).username);
		CPrint::GetInst()->PrintText(18 + strlen(GameRoom.GetUserInfo(0).username), 19, " ������ ����Ǿ����ϴ�.");
	case SYS_DEL_PL:
		CPrint::GetInst()->PrintText(0, 18, "SYSTEM :: ���� ������ �����Ǿ����ϴ�.");
		break;
	case ERR_WR_NUM:
		CPrint::GetInst()->PrintText(0, 18, "ERROR_ :: Ʋ�� ��ȣ�Դϴ�.");
		break;
	case ERR_WR_STR:
		CPrint::GetInst()->PrintText(0, 18, "ERROR_ :: Y �Ǵ� N�� �Է��ϼ���.");
		break;
	case SYS_EMPTY:
		CPrint::GetInst()->PrintText(0, 18, "ERROR_ :: ���� ����ֽ��ϴ�.");
		break;
	case ERR_FINE:
		CPrint::GetInst()->PrintText(0, 18, "...");
	default:
		ErrNum = ERR_FINE;
		break;
	}
}