#pragma once
#include <stdio.h>

void inCSV();	//takes three integers and string from statistics.txt, then write them in inCSV.csv (takes data row by row)

void inCSV()
{
	int gameID, points, numberOfWins;
	char* string[101];
	FILE* fp, *fp1;
	if ((fp = fopen("statistics.txt", "r")) != NULL)		//opens textual file
	{
		if ((fp1 = fopen("inCSV.csv", "w")) != NULL)		//opens CSV file
		{
			char s[101];
			fscanf(fp, "%d %d %d %s", &gameID, &points, &numberOfWins, string);
			fprintf(fp1, "%d,%d,%d,%s\n", gameID, points, numberOfWins, string);

			while (fgets(s, 101, fp) != NULL)
			{
				fscanf(fp, "%d %d %d %s", &gameID, &points, &numberOfWins, string);
				fprintf(fp1, "%d,%d,%d,%s\n", gameID, points, numberOfWins, string);
			}
			fclose(fp1);
			fclose(fp);
		}
	}
}