#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void Game_two()
{
    FILE *fp;
    int points = 0;
    if ( (fp = fopen("Test.txt", "r")) != NULL)
    {
        char pitanje[35], odg1[15], odg2[15], odg3[15], c;
        int  unos_odg, tac_odg, i;
        int  random_number, redni_br_pitanja = 0,  svi_odg_tacni = 0, pocetni_pomjeraj = 0, niz[5] ;
        for(i = 0; i < 5; i++)
        {
            int j = 0, redni_br_pitanja = 0;
            if ( i == 0)
            {
            random_number = rand() % 5;
            niz[0] = 0;
            }
            else
            {
                while ( j < i )
                {
                    if ( niz[j] == random_number)
                    {
                        random_number = rand() % 5;
                        j = 0;
                    }
                    j++;
                }
            }
        niz[i] = random_number;
        int pocetni_pomjeraj = 0;
        while ( (c = fgetc(fp)) != EOF && redni_br_pitanja < random_number )
        {
                    if ( c == '!')
                        redni_br_pitanja++;
                    pocetni_pomjeraj++;
        }
        fseek(fp, pocetni_pomjeraj + redni_br_pitanja * 6, SEEK_SET);
        fscanf(fp, "%s", pitanje);
        fseek(fp, strlen(pitanje) + pocetni_pomjeraj + redni_br_pitanja * 6, SEEK_SET);
        fscanf(fp, "%s", odg1);
        fscanf(fp, "%s", odg2);
        fscanf(fp, "%s", odg3);
        fscanf(fp, "%d", &tac_odg);
        printf("%d. %s\n", i + 1,  pitanje);
        printf("1) %s\n", odg1);
        printf("2) %s\n", odg2);
        printf("3) %s\n", odg3);
        do
        {
        printf("Unesi odgovor 1,  2, ili 3: ");
        scanf("%d", &unos_odg);
        } while ( unos_odg < 1 || unos_odg > 3);
        if ( unos_odg == tac_odg)
        {
            printf("TACAN ODGOVOR!\n");
            printf("DOBILI STE 20 BODOVA!\n\n");
            points += 20;
            svi_odg_tacni++;
        }
        else
        {
            printf("NETACAN ODGOVOR!\n");
            printf("IZGUBILI STE 30 BODOVA!\n\n");
            points -= 30;
        }
        if (svi_odg_tacni == 4)
        {
            printf("CESTITAM! DOBILI STE BONUS 50 BODOVA ZA SVE TACNE ODGOVORE!\n\n");
            points += 50;
        }
        redni_br_pitanja = 0, pocetni_pomjeraj = 0;
        }
        printf("\n");
        fclose(fp);
    }
    printf("\nUKUPAN BROJ BODOVA NA KRAJU OVE IGRE JE: %d \n", points);
}

