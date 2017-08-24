#include <stdio.h>

int main(void)
{
	char a[3][4];
	char *b[3][4];
	char (*c)[3][4];
	char  *x[5];
	char (*y)[5];
	printf("%lx, %lx\n", a+1 , a);
	printf("%lx, %lx\n", b+1 , b);
	printf("%lx, %lx\n", c+1 , c);
	printf("%lx, %lx\n", x+1 , x);
	printf("%lx, %lx\n", y+1 , y);
	return 0;
}
