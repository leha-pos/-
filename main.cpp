#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

#define SIZE 100

void ShowMenu()
{
	printf("1.Запуск процесса\n");
	printf("2.Вывести список запущенных процессов\n");
	printf("3.Завершить процесс\n");
	printf("4.Вывести список модулей процесса\n");
	//
	//
	//
	printf("Введите номер операции: ");
}

void StartProcess()
{
	
}

void PrintProcessList()
{
	system("CLS");
	HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	PROCESSENTRY32 peProcessEntry;
	TCHAR szBuff[1024];
	DWORD dwTemp;
	HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(INVALID_HANDLE_VALUE == hSnapshot)
	{
		return;
	}
	peProcessEntry.dwSize = sizeof(PROCESSENTRY32); 
	int i;
	i = Process32First(hSnapshot, &peProcessEntry);
	printf("Cписок запущенных процессов:\n");
	printf("|ID    |     Имя исполн.файла    |Кол-во потоков | Базовый приоритет|\n");
	do
	{
		//printf(" %d %15s %d\n",peProcessEntry.th32ProcessID, peProcessEntry.szExeFile ,peProcessEntry.cntThreads);
		wsprintf(szBuff, L" %5d %25s %12d  %12d\n",peProcessEntry.th32ProcessID, peProcessEntry.szExeFile ,peProcessEntry.cntThreads,peProcessEntry.pcPriClassBase);
		WriteConsole(hStdOut, szBuff, lstrlen(szBuff), &dwTemp, NULL);
		//PrintModuleList(hStdOut, peProcessEntry.th32ProcessID);
	}while(Process32Next(hSnapshot, &peProcessEntry));
	CloseHandle(hSnapshot);
	_getch();
}


void main()
{
	SetConsoleOutputCP(1251);	
	SetConsoleCP(1251);

	int key;
	while(1)
	{
		system("CLS");
		ShowMenu();
		key = _getch();
		switch(key)
		{
			case '1':
				StartProcess();
				break;
			case '2':
				PrintProcessList();
				break;

			default:
				printf("Неверный ввод\n");
				break;

		}
	}
}
