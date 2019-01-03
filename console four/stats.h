#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
void ShowStatistics()
{
	FILE *stats; fopen_s(&stats, "statistics.txt", "r");
	int game_id; // 1-first game 2-second.. 4.. 
	int points; 
	char date[25]; 
	if (stats)
	{
		cls();
		MoveCursorToMid();
		for (int i = 0; i > 10; i++)
		{
			fscanf_s(stats,"%d %d %s", &game_id, &points, date);
			if (game_id == 1) printf("%d)Pogadjanje broja ", i + 1);
			else if (game_id == 2) printf("%d)Kviz             ", i + 1);
			else if (game_id == 3) printf("%d)Loto             ", i + 1);
			else if (game_id == 4) printf("%d)IX-OX            ", i + 1);
			printf("%d  %s ", points, date);
			MoveCursorNextRow();
		}
	}
	return; 

}
