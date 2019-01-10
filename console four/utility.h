#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
 #define DELAY 1000				//delay from "pozdrav ime" to main menu 
#define DELAY_ERROR 400			//delay between menus 
char* Time()					// returns system time 
{
	struct tm tm;		
	localtime_s(&tm, &(time_t) { time(NULL) });
	char *time=malloc(26);
	asctime_s(time, 26, &tm);
	return time;
} 
void ShowStatistics();
#define true 1
#define false 0
void StartCheck() 
{ 
FILE *dat, *dat1;
fopen_s(&dat, "config.txt", "r+");
if (dat == NULL)
{
	fopen_s(&dat1, "config.txt", "w");
	fprintf_s(dat1, "%d %d %d", 0, 0, 0);
	fclose(dat1);
}
}
void MoveCursorNextRow()			//moves cursor to middle of screen 
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
		scanf_s("%c", &x,1);
		if (isalpha(x)) { x = '0'; err=1; }
		f = atoi(&x);
		if ((f >= 1) && (f <= 6)) break; 
		if ((f < 1) || (f > 6)) { err = 1; }
		if ( (err==1) && ((isdigit(f)==0) || (f<1) || (f>6)) )	// check is input valid
						{
						MoveCursorNextRow();
						printf("Greska! Unesite validan broj! ;)");
						err = 0; 
						Sleep(DELAY_ERROR); 
						printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"); 
						printf("                                                                ");
						printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
						}					// deletes invalid inputs 

	}	
	switch (x)
	{
	case '1':
		cls();
		prvaIgra(0, 0, 0); 
		break;
	case '2':
		cls();
		Game_two();
		break;
	case '3':
		cls();
		Game_Three();
		break;
	case '4':
		cls();
		game_four();
		break;
	case '5':
		ShowStatistics();
		break;
	case '6':
		return;
		break;
	}
}
void CreateNewUser(char *username)		//adding new user 
{
	FILE *users1;
	fopen_s(&users1, "user.txt", "w");
	if (users1) {
		fprintf_s(users1, "%s \n", username);
		fclose(users1);
	}
}
void LogIn()
{
	MoveCursorToMid(); 
 	if (IsThereUser()==0) {
 		char *name=malloc(sizeof(char)*20);
		printf("Unesite korisnicko ime:  \n   ");
		MoveCursorNextRow();
		fgets(name, 20, stdin);		// creating new user if it's first log in 
		CreateNewUser(name);
	}			
	else
	{
		char  buffer[20];
		FILE *users;
		fopen_s(&users, "user.txt", "r");
		fgets(buffer, 20, users);
		MoveCursorNextRow();		// load in user name and go to main menu
		printf("POZDRAV %s", buffer);
		Sleep(DELAY);
		Beep(1500, 500);
		MainMenu(); 
	}
}
int IsThereUser()	
{
	FILE *users; 
	fopen_s(&users,"user.txt", "r");	// check existance of user 
	char  buffer[20];					// for first  playing  
	if (users)							 
	{ 
		if(fgets(buffer, 20, users )>=0) return 1; 
		fclose(users);
	}
	else return 0; 
}

