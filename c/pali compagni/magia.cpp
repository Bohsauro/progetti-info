#include<stdio.h>
int main(){
	printf("***magic show***");
	int n; int seme;
	do{
	printf("inserisci un numero: ");
	scanf("%d", &seme);
	}while(n < 0 || n > 13);
	printf("\n\n adesso provo ad indovinare la tua carta...");
	printf("\nla tua carta e' il %d", n);
	
	switch(seme){
		case 1: printf("di cuori"); break;
		case 2: printf("di quadri"); break;
		case 3: printf("di picche"); break;
		case 4: printf("di fiori"); break;
	}
}