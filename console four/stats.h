#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
/*Returns the length of the str passed*/
int length(char *str)
{
	int characterCount = 0;

	while (str[characterCount] != '\0')
	{
		characterCount++;
	}
	return characterCount;
}
/*Starts looking for substring parameter in string from the passed start index*/
int indexOf(char *string, char *subString, int start)
{
	int flag;
	int indexOf = -1;
	int loopEnd = (int)(length(string) - length(subString));
	for (int i = start; i <= loopEnd; i++)
	{
		flag = 1;
		for (int index = 0; index < length(subString); index++)
		{
			if (string[i] != subString[index])
			{
				flag = 0;
				break;
			}
			else
			{
				i++;
			}
		}
		if (flag == 1)
		{
			indexOf = (int)(i - length(subString));
			break;
		}
	}

	return indexOf;
}
/*Helper function that returns the count of a particular delimiter in the string passed*/
int countOf(char *string, char *searchString)
{
	int index;
	int delimiterTally = 0;
	int start = 0;
	while (true)
	{
		index = indexOf(string, searchString, start);
		if (index != -1)
		{
			delimiterTally++;
		}
		else
		{
			break;
		}
		start = index + 1;
	}

	return delimiterTally;
}
/*Helper function that returns the substring*/
char* subString(char* string, int start, int length)
{
	char *a = (char*)malloc(length + 1);
	int index;
	for (index = 0; index<length; index++)
	{
		a[index] = string[index + start];
	}
	a[index] = '\0';
	return a;
}
/*Main driver function*/
char *string_replace(char *string, char *replaceFor, char *replaceWith)
{
	if (string == NULL || replaceFor == NULL || replaceWith == NULL)
	{
		return NULL;
	}
	int index;
	int subStringCount = countOf(string, replaceFor);
	/*One option to free the allocated memory here is for the caller to handle it.

	Another approach is to have the buffer as a method input parameter to make our intentions of who's

	going to handle the freeing part very clear
	*/
	char *replacedString = (char*)malloc(length(string) - length(replaceFor) * subStringCount + length(replaceWith) * subStringCount);
	int start = 0, prevCount = 0, count = 0;
	while (true)
	{
		index = indexOf(string, replaceFor, start);
		if (index != -1)
		{
			for (int i = 0; i < index - prevCount; i++)
			{
				replacedString[count] = string[i + prevCount];
				count++;
			}
			for (int i = 0; i < length(replaceWith); i++)
			{
				replacedString[count] = replaceWith[i];
				count++;
			}
			prevCount = (int)(index + length(replaceFor));
		}
		else
		{
			break;
		}
		start = (int)(index + length(replaceFor));
	}
	char *temp = subString(string, prevCount, (int)length(string) - prevCount);
	for (int i = 0; i < length(temp); i++)
	{
		replacedString[count] = temp[i];
		count++;
	}
	replacedString[count] = '\0'; 
	return replacedString;
}
void StatsUpdate(int game_id, char *time_played, int points, int number_of_wins)
{
	FILE *stats; fopen_s(&stats, "statistics.txt", "r");
	FILE *tmp; fopen_s(&tmp, "tmp.txt", "w"); 
	if (stats) {
		int gameidx, pointsx, numberofwinsx;
		char *timex = malloc(30);
		char *a = malloc(1); char *b = malloc(1); a = "-"; b = " "; 
		time_played = string_replace(time_played, b, a); 
 		int counter = 0;
		for (int i = 0; i < 10; i++)
		{
			fscanf_s(stats, "%d %d %d %s", &gameidx, &pointsx, &numberofwinsx,timex,30);
					if (number_of_wins>numberofwinsx && counter==0)		// writing in order  
					{	  
						fprintf_s(tmp, "%d %d %d %s", game_id, points, number_of_wins, time_played,30);  
						counter++; //edit one line only, rewrite else 
					}	
					else
					{
						fprintf_s(tmp, "%d %d %d %s", gameidx, pointsx, numberofwinsx, timex,30);
						fprintf_s(tmp, "\n");				  
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
