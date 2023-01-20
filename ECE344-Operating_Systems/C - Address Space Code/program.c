#include <stdlib.h>
#include <stdio.h>
int a = 5;

int f(int x);

int
main(int argc, char *argv[])
{
	int b = 10, c = 0;
	printf("b = %d\n", b);
	c = f(b+c);
}

int f(int x)
{
	int y = x;
	int *heap1 = malloc(sizeof(int));
	int *heap2 = malloc(sizeof(int));
	*heap1 = 10;
	*heap2 = 20;
	return y;
}   
