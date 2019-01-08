#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
void format_time(char *output){
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    sprintf(output, "[%d %d %d %d:%d:%d]",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}
time_t date_string_to_time(const char *date) {
	struct tm tm = { 0 }; // Important, initialize all members
	sscanf(date, "[%d %d %d %d:%d:%d]", &tm.tm_mday, &tm.tm_mon, &tm.tm_year,
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
int CheckKeyFormat(char* key)//provjerava format ključa i vraća 0 ili 1 u zavisnosti
{
	if (strlen(key) != 19)
		return 0;
	for (int i = 0; i < strlen(key)+1; i++)
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
int CheckKeyValidity(char* key,int gamenumber)//provjerava validnost ključa a ako je ispravan poziva funckiju WriteKeyTimer(int,int)
{
	FILE dat;
	if ((dat = fopen("keys.h", "r")) != NULL)
	{
		char filekey[20];
		int nmb, duration, active;
		while (fscanf(dat, "%d %d %s %d", &active, &nmb, filekey, &duration) != EOF)
		{
			if (active == 1)
				return -1;//ako je ključ već prije aktiviran onda je nevažeći i funckija vraća -1 u tom slučaju
			else if (!strcmp(key, filekey) && nmb == gamenumber)
			{
				WriteKeyTimer(gamenumber, duration);
				fseek(dat, -1, SEEK_CUR);
				fprintf(dat, "%d %d %s %d", 1, nmb, filekey, duration);
				rewind(dat);
				fclose(dat);
				return 1;
			}
		}
		rewind(dat);
		fclose(dat);
	}
	return 0;//ako je ključ pogrešan tj. ne postoji vraća 0
}
int CheckKeyTimer(int gamenumber,struct tm *timer)
{
	FILE dat;

	if (dat = fopen("keys_timer.txt", "r"))
	{
		int nmb, duration;
		char time[27];
		do
		{
			fscanf("%d %s %d", &nmb, time, &duration);
		} while (nmb != gamenumber);
		if (!duration)
			return -1;//vraća -1 ako je trajanje ključa 0 tj. ako igrica uopšte nije aktivirana
		else
		{
			struct tm currenttm;
			localtime_s(&currenttm, &(time_t) { time(NULL) });
			time_t temp=date_string_to_time(&time);
			double diff = difftime(currenttm, temp);
			if (diff > duration)
				return 0;//ako je isteklo trajanje ključa vraća 0
			else
				return 1;//ako nije isteklo vraća 1
		}
	}
}
void WriteKeyTimer(int gamenumber,int duration)//upisuje u drugi txt fajl broj igrice na koju se ključ odnosi, njegov datum upisivanja i trajanje ključa u danima
{
	FILE *dat,*temp;
	int tmpgn, tmpdur;
	if (dat = fopen("keys_timer.txt", "r"))
	{
		char *time = malloc(sizeof(char) * 26);
		rewind(dat);
		if (temp = fopen("temp.txt", "w"))
		{
			while (fscanf(dat, "%d %s %d", &tmpgn,time,&tmpdur))
				fprintf(dat, "%d %s %d", tmpgn, time, tmpdur);
			format_time(time);
			fprintf(dat, "%d %s %d", gamenumber, time, duration);
		}
		remove("keys_timer.txt");
		rename("temp.txt", "keys_timer.txt");
		rewind(temp);
		fclose(temp);
		fclose(dat);
	}
}
