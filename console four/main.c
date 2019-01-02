#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
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