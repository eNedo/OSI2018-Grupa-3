#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
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
void LogIn()
{
	MoveCursorToMid(); 
	char  name[20];
  	printf("Unesite korisnicko ime:  \n   "); 
	MoveCursorNextRow(); 
	fgets(name, 20, stdin);
	
}

boolean IsUserValid(char username)
{
	FILE *users; 
	fopen_s(&users,"users.txt", "r");
	char buffer[20]; 
	if (users)
	{ 
		for (; ((fscanf_s(users, "%s", buffer) <= 0)) ; ) 
			if (strcmp(buffer, username) == 0) return 1;
	}
	else 
		return 0; 
}


