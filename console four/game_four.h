#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>

game_four()
{
    

int is_empty(char mat[][3],int i,int j){if(mat[i][j]=='X'|| mat[i][j]=='O')return 0;else return 1;}
int is_empty_with_text(char mat[][3],int i,int j){if(mat[i][j]=='X'|| mat[i][j]=='O'){printf("Pozicija je popunjena.");getch();return 0;}else return 1;}


void board(char mat[][3])
{
    system("cls");
    printf("\n\n\tTic Tac Toe\n\n");

    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");


    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n",mat[0][0],mat[0][1],mat[0][2]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n",mat[1][0],mat[1][1],mat[1][2]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n",mat[2][0], mat[2][1],mat[2][2]);

    printf("     |     |     \n\n");
}

int win(char mat[][3],char sign)
{
    if((mat[0][0]==sign && mat[0][1]==sign && mat[0][2]==sign)
       || (mat[1][0]==sign && mat[1][1]==sign && mat[1][2]==sign)
       || (mat[2][0]==sign && mat[2][1]==sign && mat[2][2]==sign))
       return 1;
    else if((mat[0][0]==sign && mat[1][0]==sign && mat[2][0]==sign)
       || (mat[0][1]==sign && mat[1][1]==sign && mat[2][1]==sign)
       || (mat[0][2]==sign && mat[1][2]==sign && mat[2][2]==sign))
       return 1;
      else if((mat[0][0]==sign && mat[1][1]==sign && mat[2][2]==sign)
       || (mat[2][0]==sign && mat[1][1]==sign && mat[0][2]==sign))
       return 1;
       else
        return 0;
}
int game_over_igr(char mat[][3],int brojac)
{
    if(win(mat,'X'))
    {
        board(mat);
        printf("X je pobjedio.\n");
        return 1;
    }
      else if(win(mat,'O'))
        {
            board(mat);
            printf("O je pobjedio.\n");
            return 1;
        }
       else if (brojac==9)
        {
            board(mat);
            printf("nereseno:)\n");
            return 1;
        }
        else return 0;
}
int is_exsist(int niz[],int choice,int counter)
{

    for(int i=0;i<counter;i++)
        if(choice==niz[i])
       {printf("Mjesto je popunjeno.\n");
       getch();
       return 1;
       }
        return 0;
}
int is_exsist_for_bot(int niz[],int choice,int counter)
{

    for(int i=0;i<counter;i++)
        if(choice==niz[i])
       return 1;
        return 0;
}

void convert_from_number(int broj,int *i,int *j)
{

    if(broj<4){*i=0;*j=broj-(*i);}
    else if(3<broj && broj<7){*i=1;*j=broj-(*i);}
    else {*i=2;*j=broj-(*i);}
    printf("i:%d j:%d ",*i,*j);
    getch();
}
int is_0_1(int m)
{
    if(m==1)
        return 1;
    else if(m==0)
        return 1;
        else return 0;

}
int main()
{
    int number_of_wins=0,points=0;
int m=1;
while(m)
{

int counter=0,choice=0,player=2;
char mat[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
char sign;
do
{
    choice=0;
    board(mat);
player = (player % 2) ? 1 : 2;
        if(player==1)
            {int red,colone;
                do{
                        board(mat);
        printf("Player %d, enter a number:", player);
        scanf("%d", &choice);
        sign='X';
red=--choice/3;
colone=choice%3;
choice++;}
        while(!is_empty_with_text(mat,red,colone));
counter++;
if(choice<10 && choice>0)
 {mat[red][colone]=sign;}
  else{
        printf("Invalid move ");
  getch();
            player--;
            counter--;
        }
        }
        if(player==2)
        {int c=counter;sign='O';
        if(counter==0)
        {mat[1][1]=sign;counter++;}
        for(int k=0;k<3;k++)
                for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
            {
                if(i==k && c==counter)
                {
                    if((mat[i][0]==sign) && (mat[i][1]==sign) ){if(is_empty(mat,i,2)){mat[i][2]='O';counter++;}}
                    else if(mat[i][0]==sign && mat[i][2]==sign){if(is_empty(mat,i,1)){mat[i][1]='O';counter++;}}
                        else if(mat[i][1]==sign && mat[i][2]==sign){if(is_empty(mat,i,0)){mat[i][0]='O';counter++;}}
                }
            }

for(int k=0;k<3;k++)
                for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
            {
                if(j==k && c==counter)
                {
                    if((mat[0][j]==sign) && (mat[1][j]==sign) ){if(is_empty(mat,2,j)){mat[2][j]='O';counter++;}}
                    else if(mat[0][j]==sign && mat[2][j]==sign){if(is_empty(mat,1,j)){mat[1][j]='O';counter++;}}
                        else if(mat[1][j]==sign && mat[2][j]==sign){if(is_empty(mat,0,j)){mat[0][j]='O';counter++;}}
                }
            }
            if(c==counter)
            {
                if(mat[0][0]==sign && mat[1][1]==sign){if(is_empty(mat,2,2)){mat[2][2]='O';counter++;}}
               else if(mat[0][0]==sign && mat[2][2]==sign){if(is_empty(mat,1,1)){mat[1][1]='O';counter++;}}
               else if(mat[1][1]==sign && mat[2][2]==sign){if(is_empty(mat,0,0)){mat[0][0]='O';counter++;}}

              else if(mat[0][2]==sign && mat[1][1]==sign){if(is_empty(mat,2,0)){mat[2][0]='O';counter++;}}
               else if(mat[2][0]==sign && mat[1][1]==sign){if(is_empty(mat,0,2)){mat[0][2]='O';counter++;}}
               else if(mat[2][0]==sign && mat[2][0]==sign){if(is_empty(mat,1,1)){mat[1][1]='O';counter++;}}
            }
            sign='X';
for(int k=0;k<3;k++)
                for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
            {
                if(i==k && c==counter)
                {
                    if((mat[i][0]==sign) && (mat[i][1]==sign) ){if(is_empty(mat,i,2)){mat[i][2]='O';counter++;}}
                    else if(mat[i][0]==sign && mat[i][2]==sign){if(is_empty(mat,i,1)){mat[i][1]='O';counter++;}}
                        else if(mat[i][1]==sign && mat[i][2]==sign){if(is_empty(mat,i,0)){mat[i][0]='O';counter++;}}
                }
            }

for(int k=0;k<3;k++)
                for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
            {
                if(j==k && c==counter)
                {
                    if((mat[0][j]==sign) && (mat[1][j]==sign) ){if(is_empty(mat,2,j)){mat[2][j]='O';counter++;}}
                    else if(mat[0][j]==sign && mat[2][j]==sign){if(is_empty(mat,1,j)){mat[1][j]='O';counter++;}}
                        else if(mat[1][j]==sign && mat[2][j]==sign){if(is_empty(mat,0,j)){mat[0][j]='O';counter++;}}
                }
            }
            if(c==counter)
            {
                if(mat[0][0]==sign && mat[1][1]==sign){if(is_empty(mat,2,2)){mat[2][2]='O';counter++;}}
               else if(mat[0][0]==sign && mat[2][2]==sign){if(is_empty(mat,1,1)){mat[1][1]='O';counter++;}}
               else if(mat[1][1]==sign && mat[2][2]==sign){if(is_empty(mat,0,0)){mat[0][0]='O';counter++;}}

              else if(mat[0][2]==sign && mat[1][1]==sign){if(is_empty(mat,2,0)){mat[2][0]='O';counter++;}}
               else if(mat[2][0]==sign && mat[1][1]==sign){if(is_empty(mat,0,2)){mat[0][2]='O';counter++;}}
               else if(mat[2][0]==sign && mat[2][0]==sign){if(is_empty(mat,1,1)){mat[1][1]='O';counter++;}}
            }
                        sign='O';
for(int k=0;k<3;k++)
                for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
            {
                if(i==k && c==counter)
                {
                    if((mat[i][0]==sign) && is_empty(mat,i,1) && is_empty(mat,i,2) ){{mat[i][2]='O';counter++;}}
                    else if(mat[i][1]==sign && is_empty(mat,i,0) && is_empty(mat,i,2)){{mat[i][2]='O';counter++;}}
                        else if(mat[i][2]==sign && is_empty(mat,i,0) && is_empty(mat,i,1)){{mat[i][1]='O';counter++;}}
                }
            }

for(int k=0;k<3;k++)
                for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    if(j==k && c==counter)
            {

                    if((mat[0][j]==sign) && is_empty(mat,1,j) && is_empty(mat,2,j) ){{mat[2][j]='O';counter++;}}
                    else if(mat[1][j]==sign && is_empty(mat,0,j) && is_empty(mat,2,j)){{mat[2][j]='O';counter++;}}
                        else if(mat[2][j]==sign && is_empty(mat,0,j) && is_empty(mat,1,j)){{mat[1][j]='O';counter++;}}
            }

             for(int f=1;f<10 && c==counter;f++)
                {int red,colone;
          red=--f/3;
          colone=f%3;
          f++;

                    if(is_empty(mat,red,colone))
          {
              mat[red][colone]='O';
              counter++;
            }
          }
             }



        player++;
        if(win(mat,'X'))
            number_of_wins++;

}
while(!game_over_igr(mat,counter));

do
    {printf("New game: Yes[1] No[0]:");scanf("%d",&m);}while(!is_0_1(m));

}
int game_id=4;
points=0;
StatsUpdate(game_id,Time(),points,number_of_wins);
return 0;
}
}
