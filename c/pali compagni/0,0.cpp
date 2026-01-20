#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define AZZURRO "\033[1;36m"
int main()
{
   char board[3][3];
   int row;
int col;
   int i;
   int j;
   int t;
   int pcRow;
   int pcCol;
   srand(time(NULL)); // Inizializza il generatore di numeri casuali
   char winner = '0';

   for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
    board[i][j] = '-';
}
}  
   while (winner == '0') //fino non ci sono vincitori
   { for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
    printf(AZZURRO "%c ", board [i][j]);
}
       printf("\n");
}
      do{
      do{
      printf(GREEN"Mossa del giocatore:\nRiga: ");
       scanf("%d", &row);
  }while(row<1||row>3);
       do{
printf(GREEN"Colonna: ");
       scanf("%d", &col);
}while(row<1||row>3);
       board[row-1][col-1]= 'X';
  }while(board[row-1][col-1]=='O');
       if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
           winner = 'X';
       for(t=0; t<2; t++){
printf(RED"\rMossa PC.  ");
        Sleep(500);
        printf(RED"\rMossa PC.. ");
        Sleep(500);
        printf(RED"\rMossa PC...");
        Sleep(500);
}
do{
       pcRow = rand() % 3;
       pcCol = rand() % 3;
       board[pcRow][pcCol] = 'O';
}while(board[pcRow][pcCol]=='X');
if (board[0][0] == 'O' && board[1][1] == 'O'&& board[2][2] == 'O')
           winner = 'O';
system("cls");
}
if(winner=='X')
printf(AZZURRO"Hai vinto!");
if(winner=='O')
printf(RED"Il computer ha vinto.");
}