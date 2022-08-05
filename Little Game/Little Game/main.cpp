#include<stdio.h>
#include"Windows.h"

VOID ErrorExit(LPCSTR);
int main(VOID)
{
	HANDLE hStdin;
	const short bufferSize = 128;
	INPUT_RECORD irInBuf[bufferSize];
	hStdin = GetStdHandle(STD_INPUT_HANDLE);// Получаем ссылку на стандартный поток ввода(input handle)
	if (hStdin == INVALID_HANDLE_VALUE)
	{
		ErrorExit("GetStdHandle");
	}
	int index = 0;// счетчик итераций цикла обновления
	int eventsCount = 0;// счетчтик возникших событий
	int x = 10;
	int y = 10;

	while (index < 10000000)// почти бесконечный цикл, чтобы программа закрылась тогда когда мы захотим
	{
		// Получаем информацию  о событиях
		DWORD cNumRead = 0;
		BOOL peekSuccessful = PeekConsoleInput
		(
			hStdin,//ссылка на поток ввода
			irInBuf,// буфер, в котором будет помещена информация о событиях
			bufferSize,//размер буфера информации о событиях
			&cNumRead
		);
		//После вызова PeekConsoleInput получается следующее:
		//irInBuf содержит массив с информацией о событиях
		//cNumRead содержит число - фактическое количество прочитанных событий
		//peekSuccessful будет false, если случилась какая-нибудь системная ошибка
		//-----------------
		if (!peekSuccessful) { ErrorExit("PeekConsoleInput"); }//если случилась системная ошибка, выходим
		//Удаляю все накопленные сообщения и выхожу в случае ошибки
		if (!FlushConsoleInputBuffer(hStdin)) { ErrorExit("FlushConsoleInputBuffer"); }
		
		eventsCount += cNumRead;
		printf("iteration %d total %d current %d player coordinates (%d,%d)\n", index, eventsCount, cNumRead,x,y);
		// обрабатываю информацию о событиях
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