//array
#include <stdio.h>
int main(){
	int n, x, n2;
	printf("che numero vuoi moltiplicare: ");
	scanf("%d", &n);
	printf("quante volte lo vuoi moltiplicare: ");
	scanf("%d", &x);
	for(int i = 0; i < x; i++){
		n2 += n;
	}
	printf("il risultato e: %d", n2);
	
	
}