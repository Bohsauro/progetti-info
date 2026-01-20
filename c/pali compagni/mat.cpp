#include<stdio.h>
int main(){
	int mat[3][3];
	for(int i = 0; i<3; i++){ //riemppe con 1
		for(int j = 0; j<3; j++){
			mat[i][j] = 0;		
			}
	}


for(int a = 0; a < 3; a++){ //diagonale
	mat[a][a] = 1;
}

for(int b = 0; b<3; b++){ //stampa
		for(int c = 0; c<3; c++){
			printf("%d", mat[b][c]);		
		}
	printf("\n");
	}
	
}