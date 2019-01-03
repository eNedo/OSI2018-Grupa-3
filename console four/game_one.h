#pragma once
#include <stdio.h>
#include <time.h>
#include <Windows.h>

void prvaIgra(int brojIgranja, int pobijede, int gubici);		// brojIgranja - ukupan broj pokretanja PRVE IGRE od strane korisnika; broj pobijeda, broj gubitaka

void proces(int, int, int);
unsigned nasumicanBroj(int);
int dodjelaBodova(int);
int postotak(int, int);



void prvaIgra(int brojIgranja, int pobijeda, int gubitak)
{
	proces(brojIgranja, pobijeda, gubitak);
}

void proces(int brojIgranja, int pobijeda, int gubitak)
{
	unsigned unos = 101, rezultat = nasumicanBroj(11);
	int brojac = 5, rb = 1, posto = postotak(pobijeda, gubitak);
	printf("Potrebno je da pogodite broj u intervalu 0-100\n\n");
	unsigned namjestanje = 6;
	if (brojIgranja <= 3)
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
				scanf("%u", &unos);
				if ((unos > 100) || (unos < 0))
				{
					printf("\nUneseni broj nije u datom intervalu.\n\n");
					rb--;
				}
			} while ((unos > 100) || (unos < 0));

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
			printf("Izgubili ste. ");
			printf("\nTrazeni broj je broj %u.\n", rezultat);
			printf("Osvojili ste 0 bodova.\n");
		}
	}
}


//Pomocne funkcije

int dodjelaBodova(int brojPokusaja)
{
	return (100 / brojPokusaja);
}

unsigned nasumicanBroj(int namjestanje)
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