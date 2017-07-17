#include "GameRoom.h"

CGameRoom::CGameRoom()
	:ERR_USER("ERROR_ :: ������ ������ �����ϴ�.", 0, 0)
{
	Clear();
}

CGameRoom::~CGameRoom()
{
}

//�濡 ���� �߰�
ErrCode CGameRoom::AddUser(USER& tUserInfo)
{
	if (!IsFull())
	{
		users.push_back(tUserInfo);
		return ERR_FINE;
	}
	else
	{
		return ERR_ISFULL;
	}
}

//�濡 ���� ���� ���࿡ ������ ������ ���ο� ���� ����
ErrCode CGameRoom::DelUser(char* userName)
{
	if (1 == ReturnSize())
	{
		Clear();
		return SYS_DEL_PL;
	}
	for(iTerPos = users.begin(); iTerPos != users.end();)
	{
		if (!strcmp(iTerPos->username, userName))
		{
			if (iTerPos == users.begin())
			{
				masterUserName = (iTerPos + 1)->username;
				iTerPos = users.erase(iTerPos);
				return SYS_DEL_MS;
			}
			delete iTerPos->username;
			iTerPos->username = NULL;
			iTerPos = users.erase(iTerPos);
			return SYS_DEL_PL;
		}
		else
		{
			iTerPos++;
		}
	}
	/*
	for (vector<int>::size_type i = 0; i < users.size();)
	{
		if (!strcmp(users[i].username, userName))
		{
			if (i == MASTER)
			{
				masterUserName = users[i].username;
				return SYS_DEL_MS;
			}
			users.erase(users.begin() + i);
			return SYS_DEL_PL;
		}
		else
		{
			i++;
		}
	}*/
	return ERR_NO_PL;
}
//�濡 ������ ������ ����
bool CGameRoom::IsEmpty()
{
	return users.empty();
}

//�濡 ������ Full���� ����
bool CGameRoom::IsFull()
{
	return (MAX_SIZE == ReturnSize());
}

int CGameRoom::ReturnSize()
{
	int totalChar = users.size();
	return totalChar;
}

//������ ���� ����
USER& CGameRoom::GetUserInfo(int index)
{
	if (index >= 0 && index < ReturnSize())
	{
		return users[index];
	}
	else
	{
		return ERR_USER;
	}
}
USER& CGameRoom::GetUserInfo(char* userName)
{
	for (vector<int>::size_type i = 0; i < users.size(); i++)
	{
		if (!strcmp(users[i].username, userName))
		{
			return users[i];
		}
		else
		{
			return ERR_USER;
		}
	}
}

//���� ����
USER& CGameRoom::GetMasterUser()
{
	return users.front();
}

//�������� ���� ���� ����
USER& CGameRoom::GetLastUserInfo()
{
	return users.back();
}

//Ư�� ������ ���� ���� ����
ErrCode CGameRoom::BanUser(int index)
{
	if (index >= 0 && index < ReturnSize())
	{
		iTerPos = users.begin();
		iTerPos += index;

		return DelUser(iTerPos->username);
	}
	else
	{
		return ERR_WR_NUM;
	}
}

//��� �������� ����
void CGameRoom::Clear()
{
	users.clear();
}

