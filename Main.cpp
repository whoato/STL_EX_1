#include "Include.h"
#include "MainGame.h"


// 방에는 최대 6명
// 가장 먼저 들어온 사람이 방장.

int main()
{
	DWORD dwTime = GetTickCount();
	CMainGame MainGame;
	MainGame.Initialize();

	while (true)
	{
		if (dwTime + 100 < GetTickCount())
		{
			dwTime = GetTickCount();

			system("cls");

			MainGame.Progress();
			MainGame.Render();
		}
	}
	
	MainGame.Release();
	return 0;
}
