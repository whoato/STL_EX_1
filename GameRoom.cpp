#include "GameRoom.h"

CGameRoom::CGameRoom()
	:ERR_USER("ERROR_ :: 지정한 유저는 없습니다.", 0, 0)
{
	Clear();
}

CGameRoom::~CGameRoom()
{
}

//방에 유저 추가
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

//방에 유저 삭제 만약에 방장이 나가면 새로운 방장 지정
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
//방에 유저가 없는지 리턴
bool CGameRoom::IsEmpty()
{
	return users.empty();
}

//방에 유저가 Full인지 리턴
bool CGameRoom::IsFull()
{
	return (MAX_SIZE == ReturnSize());
}

int CGameRoom::ReturnSize()
{
	int totalChar = users.size();
	return totalChar;
}

//지정한 유저 정보
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

//방장 정보
USER& CGameRoom::GetMasterUser()
{
	return users.front();
}

//마지막에 들어온 유저 정보
USER& CGameRoom::GetLastUserInfo()
{
	return users.back();
}

//특정 순서에 들어온 유저 퇴출
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

//모든 유저정보 삭제
void CGameRoom::Clear()
{
	users.clear();
}

