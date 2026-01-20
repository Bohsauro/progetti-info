#include <stdio.h>
int main(){
	int max, y;
	int v[4] = {3, 5, 7, 9};
	for(y = 0; y < 4; y++){
		if(max < v[y]){
			max = v[y];
		}
	}
	printf("il numero piu alto e %d", max);
	
}