#include <stdio.h>
int main(){
	int cifre, numero;
	printf("inserisci il numero di cifre del numero: ");
	scanf("%d", &cifre);
	int num[cifre];
	for(int i = 0; i < cifre; i++){
		printf("\ninserisci una cifra: ");
		scanf("%d", &num[i]);
	}
	
	for(int i = 0; i < cifre; i++){
		if(num[i] != num[cifre-i-1]){
			printf("\nnon e palindromo");
			return 0;
		}
	}
	printf("e palindromo");
}