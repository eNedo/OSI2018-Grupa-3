#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
typedef int bool;
#define true 1
#define false 0
void MoveCursorNextRow()
{
	printf("\n                                                        ");
}
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
	COORD pos = { columns /3  , rows /3  };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void MainMenu()
{
	cls();
	MoveCursorToMid();
	printf("    *********************************\n");  MoveCursorNextRow();
	printf("(1) Pogadjanje zamisljenog broja \n");  MoveCursorNextRow();
	printf("(2) Kviz                         \n");  MoveCursorNextRow();
	printf("(3) Loto                         \n");  MoveCursorNextRow();
	printf("(4) IX-OX                        \n");  MoveCursorNextRow();
	printf("*********************************\n");  MoveCursorNextRow();
	printf("(5) Prikaz statistike            \n");  MoveCursorNextRow();	// main menu
	printf("(6) Izlaz                        \n");  MoveCursorNextRow();	// 1-6 
	printf("*********************************\n");  MoveCursorNextRow();
	char x;
	int f,err=0; 
	for (;;)
	{
		scanf_s("%c", &x);
		if (isalpha(x)) { x = '0'; err=1; }
		f = atoi(&x); 
		if ((f >= 1) && (f <= 6)) break; 
		if ( (err==1) && ((isdigit(f)==0) || (f<1) || (f>6)) )	// check is input valid
						{
						MoveCursorNextRow();
						printf("Greska! Unesite validan broj! ;) \n");
						err = 0; 
						}
	}	
	printf("%c", x); 
	// to be continued... \m/
 

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
	else
	{
		char  buffer[20];
		FILE *users;
		fopen_s(&users, "users.txt", "r");
		fgets(buffer, 20, users);
		MoveCursorNextRow();
		printf("POZDRAV %s", buffer);
		Sleep(3000);
		Beep(1500, 500);
		MainMenu(); 
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

