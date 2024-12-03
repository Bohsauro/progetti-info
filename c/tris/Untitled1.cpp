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
void gioca(char giocatore){
	do {
    printf("Scegli la posizione (0-8): ");
    scanf("%d", &posizione);

    if (posizione < 0 || posizione > 8 || campo[posizione] == 'x' || campo[posizione] == 'o') {
        printf("Posizione non valida o già occupata. Riprova.\n");
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
		scambia(giocatore);
	} while(vinto == false);

}
