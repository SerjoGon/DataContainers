#include<stdio.h>
#include"Windows.h"

VOID ErrorExit(LPCSTR);
int main(VOID)
{
	HANDLE hStdin;
	const short bufferSize = 128;
	INPUT_RECORD irInBuf[bufferSize];
	hStdin = GetStdHandle(STD_INPUT_HANDLE);// �������� ������ �� ����������� ����� �����(input handle)
	if (hStdin == INVALID_HANDLE_VALUE)
	{
		ErrorExit("GetStdHandle");
	}
	int index = 0;// ������� �������� ����� ����������
	int eventsCount = 0;// �������� ��������� �������
	int x = 10;
	int y = 10;

	while (index < 10000000)// ����� ����������� ����, ����� ��������� ��������� ����� ����� �� �������
	{
		// �������� ����������  � ��������
		DWORD cNumRead = 0;
		BOOL peekSuccessful = PeekConsoleInput
		(
			hStdin,//������ �� ����� �����
			irInBuf,// �����, � ������� ����� �������� ���������� � ��������
			bufferSize,//������ ������ ���������� � ��������
			&cNumRead
		);
		//����� ������ PeekConsoleInput ���������� ���������:
		//irInBuf �������� ������ � ����������� � ��������
		//cNumRead �������� ����� - ����������� ���������� ����������� �������
		//peekSuccessful ����� false, ���� ��������� �����-������ ��������� ������
		//-----------------
		if (!peekSuccessful) { ErrorExit("PeekConsoleInput"); }//���� ��������� ��������� ������, �������
		//������ ��� ����������� ��������� � ������ � ������ ������
		if (!FlushConsoleInputBuffer(hStdin)) { ErrorExit("FlushConsoleInputBuffer"); }
		
		eventsCount += cNumRead;
		printf("iteration %d total %d current %d player coordinates (%d,%d)\n", index, eventsCount, cNumRead,x,y);
		// ����������� ���������� � ��������
		for (DWORD i = 0; i < cNumRead; i++)
		{
			if (irInBuf[i].EventType == KEY_EVENT)
			{
				KEY_EVENT_RECORD key = irInBuf[i].Event.KeyEvent;
				if (key.bKeyDown){ printf("key pressed\n");	}
				else if (key.wVirtualKeyCode == 38) { y--; }
				else if (key.wVirtualKeyCode == 40) { y++; }
				else if (key.wVirtualKeyCode == 39) { x++; }
				else if (key.wVirtualKeyCode == 37) { x--; }
				printf("key %d pressed\n", key.wVirtualKeyCode);
			}
				else { printf("key released\n"); }
		}
		index++;
	}
	return 0;
}
VOID ErrorExit(LPCSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);
	ExitProcess(0);
}