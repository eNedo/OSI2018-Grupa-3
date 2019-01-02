#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
typedef int bool;
#define true 1
#define false 0
void fullscreen()
{
	system("mode 1000");			// incrase window size 
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SHOW_FULLSCREEN);	// forces full screen 
}
void cls()
{
	system("@cls||clear");		// simple clear screen 
}
void MoveCursorToMid()					
{ 
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	COORD pos = { columns/2, rows/2 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void MoveCursorNextRow() 
{
	printf("\n                                                                                     ");
}
void CreateNewUser(char *username)		//adding new user 
{
	FILE *users1;
	fopen_s(&users1, "users.txt", "w");
	if (users1) {
		fprintf_s(users1, "%s \n", username);
		fclose(users1);
	}
}
void LogIn()
{
	MoveCursorToMid(); 
 	if (IsThereUser()==false) {
 		char *name=malloc(sizeof(char)*20);
		printf("Unesite korisnicko ime:  \n   ");
		MoveCursorNextRow();
		fgets(name, 20, stdin);
		CreateNewUser(name);
	}							
}
bool IsThereUser()	
{
	FILE *users; 
	fopen_s(&users,"users.txt", "r");	// check 
	char  buffer[20];					// for first  playing  
	if (users)							 
	{ 
		if(fgets(buffer, 20, users )>=0) return true; 
		fclose(users);
	}
	else return false; 
}


