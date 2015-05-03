#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>

#define SIZE 100

using namespace std;



void ShowMenu()
{
	//printf("1.Запуск процесса\n");
	printf("2.Вывести список запущенных процессов\n");
	
	//printf("3.Быстродействие\n");
	//
	//
	printf("0.Выход\n");
	printf("Введите номер операции: ");
}

void StartProcess()
{
	//
}

void PrintModuleList(HANDLE CONST hStdOut, DWORD CONST dwProcessId) 
{
	MODULEENTRY32 meModuleEntry;
	TCHAR szBuff[1024];
	DWORD dwTemp;
	HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(
                             TH32CS_SNAPMODULE, dwProcessId);
    if(INVALID_HANDLE_VALUE == hSnapshot)
	{
		return;
	}

	meModuleEntry.dwSize = sizeof(MODULEENTRY32);
	Module32First(hSnapshot, &meModuleEntry);
	do 
	{
		wsprintf(szBuff, L"  ba: %08X, bs: %08X, %s\r\n",
        meModuleEntry.modBaseAddr, meModuleEntry.modBaseSize,
        meModuleEntry.szModule);
		WriteConsole(hStdOut, szBuff, lstrlen(szBuff), &dwTemp, NULL);
    } while(Module32Next(hSnapshot, &meModuleEntry));

    CloseHandle(hSnapshot);
    _getch();
}

void PrintProcessList()
{
	system("CLS");
	char key;
	int numberOfProcess=0;
	HANDLE hProcess;
	vector <PROCESSENTRY32> Processes;
	

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

	Process32First(hSnapshot, &peProcessEntry);
	do{

		Processes.push_back(peProcessEntry);

	}while(Process32Next(hSnapshot, &peProcessEntry));
	
	while(1)
	{
		system("CLS");
		Process32First(hSnapshot, &peProcessEntry);
		printf("Cписок запущенных процессов:\n");
		printf("|ID    |     Имя исполн.файла    |Кол-во потоков | Базовый приоритет|\n");
	
		for(int i = 0; i<Processes.size();i++)
		{
			
			if(numberOfProcess==i)
			{
				SetConsoleTextAttribute(hStdOut, (WORD) ((7 << 4) | 0));
				wsprintf(szBuff, L" %5d %25s %12d  %12d\n",Processes[i].th32ProcessID, 
							Processes[i].szExeFile ,Processes[i].cntThreads,Processes[i].pcPriClassBase);
				WriteConsole(hStdOut, szBuff, lstrlen(szBuff), &dwTemp, NULL);
				SetConsoleTextAttribute(hStdOut, (WORD) ((0 << 4) | 7));
			}
			else
			{
				wsprintf(szBuff, L" %5d %25s %12d  %12d\n",Processes[i].th32ProcessID, 
							Processes[i].szExeFile ,Processes[i].cntThreads,Processes[i].pcPriClassBase);
				WriteConsole(hStdOut, szBuff, lstrlen(szBuff), &dwTemp, NULL);
			}
		//PrintModuleList(hStdOut, peProcessEntry.th32ProcessID);
	
		}
		printf("1.Вывести список модулей процесса\n");
		printf("2.Завершить процесс\n");
		printf("0.Выход\n");
		key = _getch();
		switch(key)
		{
			case 72:
				if(numberOfProcess==0)
				{
					numberOfProcess=Processes.size()-1;
					break;
				}
				numberOfProcess--;
				break;
			case 80:
				if(numberOfProcess==Processes.size()-1)
				{
					numberOfProcess=0;
					break;
				}
				numberOfProcess++;
				break;
			case '1':
				PrintModuleList(hStdOut, Processes[numberOfProcess].th32ProcessID);
				break;
			case '2':
				hProcess = OpenProcess (PROCESS_ALL_ACCESS, false, Processes[numberOfProcess].th32ProcessID);
				TerminateProcess(hProcess, 0);
				CloseHandle(hProcess);
				return;
			
			case '0':
				return;
			default:
				break;

		}
	
	}

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
			case '0':
				return;
				
			default:
				printf("Неверный ввод\n");
				break;

		}
	}
}
