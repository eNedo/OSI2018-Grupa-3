#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int CheckKeyFormat(char* key)//provjerava format kljuèa i vraæa 0 ili 1 u zavisnosti
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

int CheckKeyValidity(char* key, int gamenumber)//provjerava validnost kljuèa a ako je ispravan poziva funckiju WriteKey(char*,int)
{
	FILE dat;
	if ((dat = fopen("keys.h", "r")) != NULL)
	{
		char filekey[20];
		int nmb, duration;
		while (fscanf(dat, "%d %s %d", &nmb, filekey, &duration)!= EOF)
			if (!strcmp(key, filekey) && nmb = gamenumber)
			{
				WriteKey(key, duration);
				rewind(dat);
				return 1;
			}
		rewind(dat);
		fclose(dat);
	}
	return 0;
}

void WriteKey(char* key, int duration)//upisuje uneseni validan kljuè i njegov datum upisivanja
{
	FILE dat;
	if (dat = fopen("keys_timer.txt", "w"))
	{
		struct tm tm;
		localtime_s(&tm, &(time_t) { time(NULL) });
		char *time = malloc(sizeof(char) * 26);
		asctime_s(time, 26, &tm);
		fseek(dat, 0, SEEK_END);
		fprintf(dat, "%s %s", key, time);
		rewind(dat);
		fclose(dat);
	}
}