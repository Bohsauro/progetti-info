#include <stdio.h>
int posizione;
char campo[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
char giocatore;
bool vinto = false;

void scambia(char gioca){
	if (gioca == 'x'){
		giocatore = 'o';
	} else{
		giocatore = 'x';
	}
}

void convinto(char campo[9]) {
    int vittoria[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}
    };

    for (int i = 0; i < 8; i++) {
        int a = vittoria[i][0];
        int b = vittoria[i][1];
        int c = vittoria[i][2];

        if (campo[a] == campo[b] && campo[b] == campo[c]) {
            vinto = true;
    	}
    }
}

void gioca(char giocatore){
	do {
    printf("%c Scegli la posizione (0-8): ", giocatore);
    scanf("%d", &posizione);

    if (posizione < 0 || posizione > 8 || campo[posizione] == 'x' || campo[posizione] == 'o') {
        printf("Posizione non valida o gia occupata. Riprova.\n");
    } else {
        break;
    }
} while (1);

	
	campo[posizione] = giocatore;
}

void mostracampo(char campo[9]){
	for(int i = 0; i < 9; i++){
		
		printf("%c", campo[i]);
		if (i == 0 || i == 1 || i == 3 || i == 4 || i == 6 || i == 7){
			printf("|");
		}
		if (i == 2 || i == 5){
			printf("\n-----\n");
		}
		
	}
	printf("\n");
}
int main(){
	
	
	
	mostracampo(campo);
	printf("chi inizia? x o o? ");
	scanf("%c", &giocatore);
	do{
		gioca(giocatore);
		mostracampo(campo);
		convinto(campo);
		if (vinto == true){
			printf("Ha vinto %c", giocatore);
		}
		scambia(giocatore);
	} while(vinto == false);

}
