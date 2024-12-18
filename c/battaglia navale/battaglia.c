#include <stdio.h>
#include <stdbool.h> // Per il tipo bool

// Variabili globali per i campi
char campo1[10][10];
char campo2[10][10];

void mostracampo(bool giocatore1) {
    char (*campo)[10] = giocatore1 ? campo1 : campo2;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c ", campo[i][j]);
        }
        printf("\n");
    }
}

void svuota(bool giocatore1) {
    char (*campo)[10] = giocatore1 ? campo1 : campo2;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            campo[i][j] = '_';
        }
    }
}

void numera(bool giocatore1) {
    char (*campo)[10] = giocatore1 ? campo1 : campo2;
    for (int i = 0; i < 10; i++) {
        campo[0][i] = '0' + i;
        campo[i][0] = '0' + i;
    }
}

bool posiziona(int colonna, int riga, char direzione, int lunghezza, bool giocatore1) {
    char (*campo)[10] = giocatore1 ? campo1 : campo2;

    // Controlla se la barca entra nel campo
    if (direzione == 'o') { // Orizzontale
        if (colonna - lunghezza / 2 < 0 || colonna + lunghezza / 2 >= 10) {
            return false;
        }
        for (int i = -lunghezza / 2; i <= lunghezza / 2; i++) {
            if (campo[riga][colonna + i] != '_') {
                return false;
            }
        }
        for (int i = -lunghezza / 2; i <= lunghezza / 2; i++) {
            campo[riga][colonna + i] = 'N';
        }
    } else if (direzione == 'v') { // Verticale
        if (riga - lunghezza / 2 < 0 || riga + lunghezza / 2 >= 10) {
            return false;
        }
        for (int i = -lunghezza / 2; i <= lunghezza / 2; i++) {
            if (campo[riga + i][colonna] != '_') {
                return false;
            }
        }
        for (int i = -lunghezza / 2; i <= lunghezza / 2; i++) {
            campo[riga + i][colonna] = 'N';
        }
    } else {
        return false;
    }

    return true;
}

void scegli_e_posiziona_barca(int lunghezza, bool giocatore1) {
    int colonna, riga;
    char direzione;
    bool possibile;

    printf("Posiziona una barca di lunghezza %d\n", lunghezza);

    do {
        printf("Seleziona la posizione centrale (colonna riga): ");
        scanf("%d %d", &colonna, &riga);

        printf("Inserisci la direzione (o = orizzontale, v = verticale): ");
        scanf(" %c", &direzione);

        possibile = posiziona(colonna, riga, direzione, lunghezza, giocatore1);

        if (!possibile) {
            printf("Posizione non valida, riprova.\n");
        }
    } while (!possibile);
}

void barche(bool giocatore1) {
    scegli_e_posiziona_barca(5, giocatore1); // Barca da 5
    scegli_e_posiziona_barca(4, giocatore1); // Barca da 4
    scegli_e_posiziona_barca(3, giocatore1); // Prima barca da 3
    scegli_e_posiziona_barca(3, giocatore1); // Seconda barca da 3
    scegli_e_posiziona_barca(2, giocatore1); // Barca da 2
}

int main() {
    svuota(true);
    svuota(false);

    numera(true);
    numera(false);

    printf("Campo del giocatore 1:\n");
    mostracampo(true);

    printf("Campo del giocatore 2:\n");
    mostracampo(false);

    barche(true); // Posizionamento barche per il giocatore 1

    printf("Campo del giocatore 1 dopo il posizionamento:\n");
    mostracampo(true);

    return 0;
}