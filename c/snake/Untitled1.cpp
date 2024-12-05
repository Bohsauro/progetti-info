#include <stdio.h>
void mostra(char campo[10][10]){
	for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c", campo[i][j]);
        }
        printf("\n");
    }
}
int main() {
    char campo[10][10];
    // bordi array
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == 0 || i == 9 || j == 0 || j == 9) {
                campo[i][j] = '#'; // bordo
            } else {
                campo[i][j] = ' '; // vuoto
            }
        }
    }

    mostra(campo);
    

    return 0;
}
