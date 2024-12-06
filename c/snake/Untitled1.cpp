#include <stdio.h>
// < > ^ ^
bool perso;
void mostra(char campo[10][10]){
	for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c", campo[i][j]);
            	printf(" ");
			
        }
        printf("\n");
    }
}
void bordi(char campo[10][10]){
	for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == 0 || i == 9 || j == 0 || j == 9) {
                campo[i][j] = '#'; 
            } else {
                campo[i][j] = ' ';
            }
        }
    }
}
void controllapos(char campo[10][10], int posizionex, int posizioney){
	if(campo[posizionex][posizioney] != ' '){
		perso = true;
	}
}
int main() {
	
    char campo[10][10];
    bordi(campo);
    mostra(campo);
    

    return 0;
}
