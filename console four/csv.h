#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
 
//takes three integers and string from statistics.txt, then write them in inCSV.csv
//(takes data row by row)
void  CSV()
{
	int gameID, points, numberOfWins;
	char* string[101];
	FILE* fp, *fp1;
	fopen_s(&fp, "statistics.txt", "r");
	fopen_s(&fp1, "inCSV.csv", "w");
	if (fp!=NULL)		//opens textual file
	{
		if (fp1!= NULL)		//opens CSV file
		{
			char s[101];
			fscanf_s(fp, "%d %d %d %s", &gameID, &points, &numberOfWins, string,30);
			fprintf_s(fp1, "%d,%d,%d,%s\n", gameID, points, numberOfWins, string,30);
			while (fgets(s, 101, fp) != NULL)
			{
				fscanf_s(fp, "%d %d %d %s", &gameID, &points, &numberOfWins, string,30);
				fprintf_s(fp1, "%d,%d,%d,%s\n", gameID, points, numberOfWins, string,30);
			}
			fclose(fp1);
			fclose(fp);
		}
		else
			printf("error!");
	}
	else
		printf("critical error!"); 
}
