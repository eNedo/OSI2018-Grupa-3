#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include "game_one.h"
#include "game_two.h"
#include "game_three.h"
#include "game_four.h"
#include "utility.h"
#include "stats.h"
#include "keys.h"
int main()
{
	fullscreen();
	LogIn();
	
 
	system("pause");
	return 0;
}





/*
struct tm tm;
localtime_s(&tm, &(time_t) { time(NULL) });
char *time = malloc(sizeof(char) * 26);
asctime_s(time, 26, &tm);
*/
