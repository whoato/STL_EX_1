#pragma once
enum COLOR
{
	검정색,
	파란색,
	초록색,
	옥색,
	빨간색,
	자주색,
	노란색,
	흰색,
	회색,
	연한파란색,
	연한초록색,
	연한옥색,
	연한빨간색,
	연한자주색,
	연한노란색,
	진한흰색,
};

enum ErrCode
{
	ERR_FINE,
	ERR_ISFULL,
	ERR_NO_PL,
	SYS_DEL_MS,
	SYS_DEL_PL,
	ERR_WR_NUM		,
	ERR_WR_STR,
	SYS_EMPTY	,
};

enum eIndex
{
	MASTER = 0	,
	LAST = 8	,
	EMPTY = 10	,
};