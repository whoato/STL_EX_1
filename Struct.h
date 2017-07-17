#pragma once
typedef struct UserInfo
{
	char* username;
	int level;
	int exp;

	UserInfo() {};

	UserInfo(int _lv, int _xp) : level(_lv), exp(_xp) {};

	UserInfo(char* _name, int _lv, int _xp) : username(_name), level(_lv), exp(_xp) {};
} USER;