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
	//�濡 ���� �߰�
	ErrCode AddUser(USER& tUserInfo);

	//�濡 ���� ���� ���࿡ ������ ������ ���ο� ���� ����
	ErrCode DelUser(char* userName);

	//�濡 ������ ������ ����
	bool IsEmpty();

	//�濡 ������ Full���� ����
	bool IsFull();

	int ReturnSize();

	//������ ���� ����
	USER& GetUserInfo(int index);
	USER& GetUserInfo(char* userName);

	//���� ����
	USER& GetMasterUser();

	//�������� ���� ���� ����
	USER& GetLastUserInfo();

	//Ư�� ������ ���� ���� ����
	ErrCode BanUser(int index);

	//��� �������� ����
	void Clear();

	
public:
	CGameRoom();
	~CGameRoom();
};

