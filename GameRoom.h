#pragma once
#include "Include.h"

class CGameRoom
{
private:
	vector<USER> users;
	char* masterUserName;
	vector<USER>::iterator iTerPos;
	USER ERR_USER;
public:
	//방에 유저 추가
	ErrCode AddUser(USER& tUserInfo);

	//방에 유저 삭제 만약에 방장이 나가면 새로운 방장 지정
	ErrCode DelUser(char* userName);

	//방에 유저가 없는지 리턴
	bool IsEmpty();

	//방에 유저가 Full인지 리턴
	bool IsFull();

	int ReturnSize();

	//지정한 유저 정보
	USER& GetUserInfo(int index);
	USER& GetUserInfo(char* userName);

	//방장 정보
	USER& GetMasterUser();

	//마지막에 들어온 유저 정보
	USER& GetLastUserInfo();

	//특정 순서에 들어온 유저 퇴출
	ErrCode BanUser(int index);

	//모든 유저정보 삭제
	void Clear();

	
public:
	CGameRoom();
	~CGameRoom();
};

