#pragma once
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
StatsUpdate(int game_id, char *time_played, int points, int number_of_wins);
int main()
{
    FILE *fp;
    char *pitanje, *odg_a, *odg_b, *odg_c, tac_odg, unos_odg;
    int duz_pit = 0, duz_a = 0, duz_b = 0, duz_c = 0, random_number; // random broj
    if ( (fp = fopen("Test.txt","r")) != NULL)
    {
        char c;
        int i = 0, j = 0, k = 0, p = 0, q = 0, m = 0, redni_br = 0, pocetna_alokacija = 0; // dodatak - broj bajtova do pocetka pitanja.
        random_number = rand() % 5;
        printf("random_number = %d   ", random_number);
        while ((c = fgetc(fp)) != EOF  && redni_br < 1)
        {
            if (c == '!')
            redni_br++;
            printf("%c %d\n", c, pocetna_alokacija);
            pocetna_alokacija++;
        }
        printf("pocetna_alokacija = %d\n", pocetna_alokacija);
        fseek(fp, pocetna_alokacija + 5, SEEK_SET); //
        while ( (c = fgetc(fp)) && c != ':'  ) // 
            duz_pit++;
        printf("\nduz_pit = %d\n", duz_pit);// premotavanje na pocetak
        pitanje = (char*)calloc(duz_pit + 1,sizeof(char)); // alociranje pitanja
        fseek(fp, pocetna_alokacija + 5, SEEK_SET);
        while ((c = fgetc(fp))  &&  c != ':') //
        {
            printf("%c", c);
            pitanje[i] = c;
            i++;
        }
        printf("\n");
        fseek(fp, duz_pit + pocetna_alokacija, SEEK_SET); // +1  premotavanje na mjesto gdje pocinje odg_a
        while ((c = fgetc(fp)) != EOF && c != ':')
        {
            duz_a++;
        }
        odg_a = (char*)calloc(duz_a, sizeof(char)); // + 1
        fseek(fp,duz_pit+ pocetna_alokacija, SEEK_SET); // + 1
        while ((c = fgetc(fp)) != EOF && c != ':')
        {
            printf("%c", c);
            odg_a[j] = c;
            j++;
        }
        fseek(fp, duz_pit + duz_a  + pocetna_alokacija, SEEK_SET); // + 1
        while ((c = fgetc(fp)) != EOF && c != ':')
        {
            duz_b++;
        }
        fseek(fp, duz_pit + duz_a  + pocetna_alokacija, SEEK_SET); // + 3
        odg_b = (char*)calloc(duz_b, sizeof(char));
        while ((c = fgetc(fp)) != EOF && c != ':')
        {
            odg_b[k] = c;
            k++;
        }
        fseek(fp, duz_pit + duz_a + duz_b + 1 + pocetna_alokacija, SEEK_SET);
        while ((c = fgetc(fp)) != EOF && c != ':')
            duz_c++;
        fseek(fp, duz_pit + duz_a + duz_b + 14 + pocetna_alokacija, SEEK_SET);
        odg_c = (char *)calloc(duz_c, sizeof(char));
        while ((c = fgetc(fp)) != EOF && c != ':')
        {
            printf(" %c ", c);
            odg_c[p] = c;
            p++;
        }
        fseek(fp, duz_pit + duz_a + duz_b + duz_c + 16 + pocetna_alokacija, SEEK_SET);
        while ((c = fgetc(fp)) != EOF && c != ':')
            tac_odg = c;
        printf("%s? \n", pitanje);
        printf("a) %s \n", odg_a);
        printf("b) %s \n", odg_b);
        printf("c) %s \n", odg_c);
        printf("tac odg %c\n", tac_odg);
        printf("UNESITE ODGOVOR (a, b, ili c): ");
        scanf("%c", &unos_odg);
        if ( unos_odg == tac_odg)
            printf("TACAN ODGOVOR!");
        else
            printf("NETACAN ODGOVOR!");
    }
    return 0;
}

