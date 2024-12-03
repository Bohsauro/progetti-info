#include<stdio.h>
int main(){
	int n, x;
	do{
		printf("inserisci il numero da controllare: ");
		scanf("%d", &n);
		if (n<=1){
			printf("il numero deve essere maggiore di 1!\n");
		}
	}
	while(n <= 1);
	x = n % 2;
	if (x == 1){
		printf("%d e' dispari!", n);
	} 
	else {
		printf("%d e' pari!", n);
	}
}
