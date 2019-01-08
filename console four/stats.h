#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "CSV.h"
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
	if (string == NULL || replaceFor == NULL || replaceWith == NULL)	return NULL;
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
	if (stats && tmp) {
		int gameidx[41], pointsx[41], numberofwinsx[41];
		char **timex = (char**)malloc(sizeof(char**)*41);
		for (int i = 0; i < 41; i++) timex[i] =(char*) malloc(sizeof(char*)); 
		char *a = malloc(1); char *b = malloc(1); a = "-"; b = " "; 
		time_played = string_replace(time_played, b, a); 
		for (int i = 0; i < 41; i++)			// input stats from file 
			fscanf_s(stats, "%d %d %d %s", &gameidx[i], &pointsx[i], &numberofwinsx[i],timex[i],30);
		gameidx[40] = game_id; pointsx[40] = points; numberofwinsx[40] = number_of_wins; timex[40] = time_played;
		for (int i=0; i<=40; i++) 
			for (int j=0; j<=40; j++)				// sorting stats data 
				if ((pointsx[i] > pointsx[j]) && (game_id==gameidx[i]))
				{
					int temp1, temp2, temp3;
					temp1 = pointsx[i]; pointsx[i] = pointsx[j]; pointsx[j] = temp1;
					temp2 = numberofwinsx[i]; numberofwinsx[i] = numberofwinsx[j]; numberofwinsx[j] = temp2;
					temp3 = gameidx[i]; gameidx[i] = gameidx[j]; gameidx[j] = temp3;
					char *temp4 = timex[i]; timex[i] = timex[j]; timex[j] = temp4;
				}
		for (int i = 0; i < 41; i++)				//output to file 
				fprintf_s(tmp, "%d %d %d %s\n", gameidx[i], pointsx[i],numberofwinsx[i], timex[i],30);
		free(a); free(b); 
		for (int i = 0; i < 41; i++)	free(timex[i]); 
		free (timex);
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
		printf("Izaberite koju statistiku zelite!");
		MoveCursorNextRow(); 
		printf("    *********************************\n");  MoveCursorNextRow();
		printf("(1) Pogadjanje zamisljenog broja \n");  MoveCursorNextRow();
		printf("(2) Kviz                         \n");  MoveCursorNextRow();
		printf("(3) Loto                         \n");  MoveCursorNextRow();
		printf("(4) IX-OX                        \n");  MoveCursorNextRow();
		printf("*********************************\n");  MoveCursorNextRow();
		char tempx; 
		int tempxx;
		for (;;)
		{
			scanf_s("%c", &tempx, 1);
			if (isdigit(tempx) > 0) { 
				tempxx = atoi(&tempx);
				if (tempxx <= 4 && tempxx >= 1) 
					break; }
		}
		cls(); 
		switch (tempxx)
		{
		case (1):
			printf("Pogadjanje zamisljenog broja   \n"); break;
		case(2):
			printf("Kviz                           \n"); break;
		case(3):
			printf("Loto                           \n"); break;
		case(4):
			printf("IX - OX                        \n"); break;
		} 
 		for (int i = 0; i < 40; i++)
		{
			fscanf_s(statsf, "%d%d%d%s", &game_id, &points, &num_of_wins, date,26);
			if (game_id == tempxx) printf("%d | %d | %s \n", points, num_of_wins,date);
 		}
		printf("\nBroj poena|Broj pobjeda|Datum igranja\n"); 
 		fclose(statsf); 
		free(date);
 		MoveCursorNextRow(); 
		printf("(1) Povratak na glavni meni!    (2) Sacuvajte statistiku u CSV fajl! (3) Izlaz iz aplikacije!"); 
		char b; 
		for (;;) {
			scanf_s("%c", &b,1);
			if ((isdigit(b) > 0)) {
				int temp;
				temp = atoi(&b); //error
				if ((temp >= 1) && (temp <= 3)) break; // troubleshoting tomorow... 
			} 
			else
			{
				printf("\b "); 
			} 
		}
		int bint = atoi(&b); 
		switch (bint)
		{
		case 1: MainMenu();			break;
		case 2:	CSV(); MainMenu();  break;
		case 3:	break;
		}

	}
	else
	{
		cls();  printf("critical error!");
	} 
 
}
