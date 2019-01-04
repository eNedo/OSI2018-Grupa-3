#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
void StatsUpdate(int game_id, char *time_played, int points, int number_of_wins)
{
	FILE *stats; fopen_s(&stats, "statistics.txt", "r");
	FILE *tmp; fopen_s(&tmp, "tmp.txt", "w"); 
	if (stats) {
		int gameidx, pointsx, numberofwinsx;
		char *timex = malloc(26); 
		int counter = 0;
		for (int i = 0; i < 10; i++)
		{
			fscanf_s(stats, "%d %d %d %s", &gameidx, &pointsx, &numberofwinsx,timex,30);
					if (number_of_wins>numberofwinsx && counter==0)		// writing in order  
					{	  
						fprintf_s(tmp, "%d %d %d %s\n", game_id, points, number_of_wins, time_played,30);  
						counter++; // only one edit of line 
					}	
					else
					{
						fprintf_s(tmp, "%d %d %d %s", gameidx, pointsx, numberofwinsx, timex, 30);
						fprintf_s(tmp, "\n");				//needs more work 
					}
 		}
		fclose(stats);
		fclose(tmp);
		remove("statistics.txt");
		rename("tmp.txt", "statistics.txt");
	}
	else
	{
		cls(); printf("Critical error! Reinstal game! \n"); 
	}
}
void ShowStatistics()
{
	FILE *statsf; fopen_s(&statsf, "statistics.txt", "r");
	int game_id; // 1-first game 2-second.. 4.. 
	int points,num_of_wins; 
	char *date=malloc(26); 
	if (statsf)
	{
		cls();
		MoveCursorToMid();
		printf("    Igra                 Broj poena         Broj pobjeda     Datum igranja   ");
		MoveCursorNextRow();

		for (int i = 0; i < 10; i++)
		{
			fscanf_s(statsf, "%d%d%d%s", &game_id, &points, &num_of_wins, date,26);
			if (game_id == 1) printf("%d)Pogadjanje broja ", i + 1);
			else if (game_id == 2) printf("%d)Kviz             ", i + 1);
			else if (game_id == 3) printf("%d)Loto             ", i + 1);
			else if (game_id == 4) printf("%d)IX-OX            ", i + 1);
			printf("         %d                 %d              %s \n", points, num_of_wins,date);
			MoveCursorNextRow();
		}
 		fclose(statsf); 
		fopen_s(&statsf, "statistics.txt", "r+");  fseek(statsf, 460, SEEK_CUR);
		for (int i = 0; i < 15; i++) fprintf(statsf, "                                           \n");   
		fclose(statsf);				// remove more than 10. entries 
	}
	else
	{
		cls();  printf("critical error!");
	} 
 
}
