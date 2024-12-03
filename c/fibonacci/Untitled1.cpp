#include <stdio.h>
#include <windows.h>

int fibonacci(int a, int b){
	printf("%d \n", a);
	printf("%d \n", b);
	a = a + b;
	b = a + b;
	Sleep(500);
	return fibonacci(a, b);
}
int main(){
	int x, y;
	x = 0;
	y = 1;
	fibonacci(x, y);
}
