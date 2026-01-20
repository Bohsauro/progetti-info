#include <stdio.h>
#include <stdlib.h>  // Per usare rand()
#include <time.h>    // Per usare time() nella semina di rand()
void inizializzare_tabellone(char tabellone[3][3]) {
   for (int i = 0; i < 3; i++) {
       for (int j = 0; j < 3; j++) {
           tabellone[i][j] = ' ';  // Inizializziamo ogni casella con uno spazio vuoto
       }
   }
}
void mostra_tabellone(char tabellone[3][3]) {
   printf("\n");
   for (int i = 0; i < 3; i++) {
       for (int j = 0; j < 3; j++) {
           printf(" %c ", tabellone[i][j]);
           if (j < 3) printf("|");
       }
       printf("\n");
       if (i < 2) printf("---|---|---\n");
   }
   printf("\n");
}
int verifica_vittoria(char tabellone[3][3], char giocatore) {
   // Controlliamo le righe e le colonne
   for (int i = 0; i < 3; i++) {
       if ((tabellone[i][0] == giocatore && tabellone[i][1] == giocatore && tabellone[i][2] == giocatore) ||  // Riga
           (tabellone[0][i] == giocatore && tabellone[1][i] == giocatore && tabellone[2][i] == giocatore)) {  // Colonna
           return 1;
       }
   }
   // Controlliamo le due diagonali
   if ((tabellone[0][0] == giocatore && tabellone[1][1] == giocatore && tabellone[2][2] == giocatore) ||
       (tabellone[0][3] == giocatore && tabellone[1][2] == giocatore && tabellone[2][1] == giocatore)) {
       return 1;
   }
   return 0;
}
int tabellone_pieno(char tabellone[4][4]) {
   for (int i = 0; i < 3; i++) {
       for (int j = 0; j < 3; j++) {
           if (tabellone[i][j] == ' ') return 0;  // Se c'è almeno una casella vuota
       }
   }
   return 1;  // Se non ci sono spazi vuoti
}
int main() {
   char tabellone[3][3];
   int riga, colonna, turno = 0;
   char giocatore_corrente;
   inizializzare_tabellone(tabellone);
   // Semina per la generazione di numeri casuali (se vuoi che il primo giocatore sia casuale)
   srand(time(NULL));  // Per randomizzare l'inizio
   while (1) {
       giocatore_corrente = (turno % 2 == 0) ? 'X' : 'O';
       mostra_tabellone(tabellone);
       printf("Turno del giocatore %c. Inserisci la riga (1-3) e la colonna (1-3): ", giocatore_corrente);
       // Inserimento del giocatore
       scanf("%d", &riga);
       scanf("%d",&colonna);
       // Verifica che le righe e le colonne siano tra 1 e 3, e che la casella sia vuota
       if (riga < 1 || riga > 3 || colonna < 1 || colonna > 3 || tabellone[riga - 1][colonna - 1] != ' ') {
           printf("Movimento non valido. Riprova.\n");
       }
       // Mettiamo la pedina del giocatore
       tabellone[riga - 1][colonna - 1] = giocatore_corrente;
       turno++;
       // Verifica se il giocatore corrente ha vinto
       if (verifica_vittoria(tabellone, giocatore_corrente)) {
           mostra_tabellone(tabellone);
           printf("Il giocatore %c ha vinto!\n", giocatore_corrente);
           break;
       }
       }
   }