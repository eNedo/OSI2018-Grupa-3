#pragma once 
#include "stats.h"
#include "utility.h"
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <ctype.h>
#include <string.h>
void proces(int, int, int);

void prvaIgra(int brojIgranja, int pobijeda, int gubitak)
{
	proces(brojIgranja, pobijeda, gubitak);
}
void proces(int brojIgranja, int pobijeda, int gubitak)
{
	int n = 1, points = 0, numberOfWins = NumberOfWins();
	while (n == 1)
	{
		unsigned unos = 101, rezultat = nasumicanBroj(101);
		int brojac = 5, rb = 1, posto = postotak(pobijeda, gubitak), valid;
		char unosString[11];
		printf("*******************************************\n");
		printf("Potrebno je pogoditi broj u intervalu 0-100\n");
		printf("*******************************************\n\n");
		unsigned namjestanje = 6;
		if (brojIgranja <= 3)	// ako korisnik nije igrao vise od tri puta PRVU igru, onda ovaj uslov omogucava pobijedu
		{
			namjestanje = nasumicanBroj(4) + 2;	// namjestanje = korak u kome korisnik pogadja
			if (namjestanje > 6)
				namjestanje = 5;
		}

		while (brojac > 0 && rezultat != unos)
		{
			do
			{
				printf("Unesite %d. broj: ", rb++);
				scanf("%s", unosString);
				valid = validanUnos(unosString);
				if (valid == -1)
				{
					printf("\nUnos nije validan. Ponovite!\n\n");
					rb--;
				}
				else
					unos = valid;
			} while (valid == -1);

			if (unos > rezultat || brojac == namjestanje)
			{
				if (brojac == namjestanje)
				{
					printf("Pogodili ste! \n\n"); brojac++;
					rezultat = unos;
					printf("\nTrazeni broj je broj %u.\n", unos);
					printf("Broj osvojenih bodova je %d.\n", dodjelaBodova(rb - 1));
				}
				else
					printf("Broj je manji.\n\n");

			}
			else if (unos < rezultat)
			{
				if (brojac == namjestanje)
				{
					printf("Pogodili ste! \n\n"); brojac++;
					rezultat = unos;
					printf("\nTrazeni broj je broj %u.\n", unos);
					printf("Broj osvojenih bodova je %d.\n", dodjelaBodova(rb - 1));
				}
				else
					printf("Broj je veci.\n\n");
			}
			else if (unos == rezultat)
			{
				if ((brojIgranja > 3) && (posto < 40))
				{
					printf("Broj je veci.\n\n");
					rezultat++;
				}
				else
				{
					printf("Pogodili ste! \n\n"); brojac++;
					printf("\nTrazeni broj je broj %u.\n", rezultat);
					printf("Broj osvojenih bodova je %d.\n", dodjelaBodova(rb - 1));
				}
			}
			brojac--;

			if (brojac == 0)
			{
				printf("\nIzgubili ste. ");
				printf("\nTrazeni broj je broj %u.\n", rezultat);
				printf("Osvojili ste 0 bodova.\n");
			}
		}
		if (brojac > 0)
		{
			points += dodjelaBodova(rb - 1);
			numberOfWins++;
		}
		else if (brojac == 0)
			IncNumberOfLosses();
		int prolaz = 0;
		while (prolaz != 1)
		{
			printf("\n\n<1> - revans\t<0> - glavni meni\n");
			char c[5] = "1";
			scanf("%s", c);
			if (c[0] == '0')	//Ako je brojac == 0 onda je izgubio
			{
				StatsUpdate(1, Time(), points, numberOfWins);
				system("CLS"); 
				MainMenu();
			}
			else if (c[0] == '1')
			{
				system("CLS"); prolaz = 1;
			}
			else
			{
				system("CLS");
				printf("Unos nije validan. Ponovite!\n");
			}
		}
	}
}

//Pomocne funkcije

int dodjelaBodova(int brojPokusaja)
{
	return (100 / brojPokusaja);
}

unsigned nasumicanBroj(int namjestanje)		//generisanje prirodnog broja [0, namjestanje]
{
	unsigned nasumican;
	time_t t;
	srand((unsigned)time(&t));
	return nasumican = rand() % namjestanje;
}

int postotak(int pobijeda, int gubitak)
{
	double ukupnoIgranja = pobijeda + gubitak;
	float postotakP, postotakG;
	postotakP = (pobijeda / ukupnoIgranja) * 100;
	postotakG = (gubitak / ukupnoIgranja) * 100;
	return (postotakG - postotakP);
}

