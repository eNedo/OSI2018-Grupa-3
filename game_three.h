#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include<ctype.h>
#include<string.h>

void game_Three()
{
	int arr[7], arr1[20];
	int n;
	int number_of_wins = 0;
	char string[11];
	int valid;
	printf("Unesite vasih 7 brojeva (1-45)\n");
	for (int i = 0; i < 7; i++)
	{
		do
		{
			printf("Unesite vas %d. broj: ", i + 1);
			scanf("%s", string);
			valid = validanUnos(string);
			n = valid;
			arr[i] = n;
			for (int j = 0; j < i; j++)
			{
				if (n == arr[j])
				{
					printf("Vec imate broj %d.\n", n);
					i--;
				}
			}
		} while (n > 45 || n < 1 || valid == -1);
	}

	printf("\n");
	printf("Vasi brojevi su: ");
	for (int i = 0; i < 7; i++)
		printf("%d ", arr[i]);
	printf("\n");
	printf("Bingo pocinje!\n\n");

	int lower = 1, upper = 45, count = 20;
	int br = 1, points = 0;
	srand(time(0));
	for (int i = 0; i < count; i++)
	{
		int num = (rand() % (upper - lower + 1)) + lower;
		arr1[i] = num;
		for (int j = 0; j < i; j++)
		{
			if (num == arr1[j])
			{
				i--;
			}
		}
	}
	for (int i = 0; i < count; i++)
	{
		if (br <= 4)
		{
			printf("Izvucen je  %d.broj:  %d  \n", i + 1, arr1[i]);
			for (int k = 0, game = 0; k < 7; k++)
			{
				if (arr1[i] == arr[k])
				{
					printf("Cestitamo! Pogodili ste broj %d. ", arr1[i]);
					game = br * 10;
					points += game;
					printf("Trenutni broj osvojenih poena: %d\n", points);
					br++;
				}
			}

		}
		else if (br > 4)
		{
			printf("Izvucen je  %d.broj:  %d  \n", i + 1, arr1[i]);
		}
	}
	printf("\nUkupno osvojenih poena: %d \n", points);
	printf("Broj pogodjenih brojeva: %d \n", br - 1);

	printf("\n");
	printf("Bingo izvuceni brojevi su: ");
	for (int i = 0; i < 20; i++)
		printf("%d ", arr1[i]);
	number_of_wins++;
}

//pomocna funkcija
int validanUnos(char* p)
{
	if ((strlen(p) > 2) && (strcmp(p, "101") >= 0))
		return -1;
	if (p[0] == '-')
		return -1;
	for (int i = 0; i < strlen(p); i++)
		if (!isdigit(p[i]))
			return -1;
	int res = atoi(p);
	return res;
}
