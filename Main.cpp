#include "Include.h"
#include "MainGame.h"


// �濡�� �ִ� 6��
// ���� ���� ���� ����� ����.

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
