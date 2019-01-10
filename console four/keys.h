#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "utility.h"
#include "stats.h"
 time_t date_string_to_time( char *date) {
	struct tm tm = { 0 }; // Important, initialize all members
	sscanf_s(date, "%d-%d-%d-%d:%d:%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year,
		&tm.tm_hour, &tm.tm_min, &tm.tm_sec);
	tm.tm_isdst = -1; // Assume local daylight setting per date/time
	tm.tm_mon--;      // Months since January
					  // Assume 2 digit year if in the range 2000-2099, else assume year as given
	if (tm.tm_year >= 0 && tm.tm_year < 100) {
		tm.tm_year += 2000;
	}
	tm.tm_year -= 1900; // Years since 1900
	time_t t = mktime(&tm);
	return t;
}
void WriteKeyTimer(int gamenumber, int duration) 
{
	FILE *dat, *temp;
	int tmpgn, tmpdur;
	char *time123 = (char*)malloc(26);
	if (dat = fopen("keys_timer.txt", "r"))
	{
		if (temp = fopen("temp.txt", "w"))
		{
			while (fscanf_s(dat, "%d %s %d", &tmpgn, time123,26, &tmpdur)!=EOF)
			{
				fprintf_s(temp, "%d %s %d\n", tmpgn, time123,26, tmpdur);
			}
			char *a = "-"; char *b = " ";
			char *c = string_replace(Time(), b, a); 
			fprintf_s(temp, "%d %s %d ", gamenumber, string_replace(c,"\n", " "),duration);
		}
		fclose(temp);
		fclose(dat);
		remove("keys_timer.txt");
		rename("temp.txt", "keys_timer.txt");
	}
}
int CheckKeyFormat(char* key) 
{
	if (strlen(key) != 19)
		return 0;
	for (int i = 0; i < strlen(key) + 1; i++)
	{
		if (key[i] < 48 || key[i]>57)
		{
			if (i != 4 && i != 9 && i != 14)
				return 0;
			else
				if (!(key[i] == '-'))
					return 0;
		}
	}
	return 1;
}
int CheckKeyValidity(char* key, int gamenumber) 
{
	FILE *dat;
	if ((dat = fopen("keys.txt", "r")) != NULL)
	{
		char filekey[20];
		int nmb, duration, active, br = 0;
		while (fscanf(dat, "%d %d %s %d", &active, &nmb, filekey, &duration) != EOF)
		{
			br++;
			if ((strcmp(key, filekey)==0) && nmb == gamenumber)
			{
				if (active == 1)
					return -1; 
				else
				{
					WriteKeyTimer(gamenumber, duration);
					char *keytemp = malloc(sizeof(char) * 26);
					rewind(dat);
					FILE *temp;
					if (temp = fopen("temp.txt", "w"))
					{
						int tmpgn, tmpdur, tmpact;
						while (fscanf(dat, "%d %d %s %d", &tmpact, &tmpgn, keytemp, &tmpdur)!=EOF)
						{
							if (strcmp(keytemp, key) == 0)
								fprintf(temp, "%d %d %s %d\n", 1, gamenumber, filekey, duration);
							else
								fprintf(temp, "%d %d %s %d\n", tmpact, tmpgn, keytemp, tmpdur);
						}
					}
					fclose(dat);
					fclose(temp);
					remove("keys.txt");
					rename("temp.txt", "keys.txt");
					return 1;
				}
			}
		} 
	}
	return 0; 
}
int CheckKeyTimer(int gamenumber)
{
	FILE *dat;
	if (dat = fopen("keys_timer.txt", "r"))
	{
		int nmb, duration;
		char timex[27];
		do
		{
			fscanf(dat, "%d %s %d", &nmb, timex, &duration);
		} while (nmb != gamenumber);
		if (duration == -1)
			return 0; 
		else if (!duration)
			return 1; 
		else
		{
			time_t currenttm;  time(&currenttm); 
 			time_t temp = date_string_to_time(time);
			double diff = difftime(currenttm, temp);
			if (diff > duration)
				return 0; 
			else
				return 1; 
		}
	}
}
 
