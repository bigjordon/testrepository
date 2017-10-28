#include <stdio.h>

int main(void)
{
	char a[3][4];
	char *b[3][4];
	char (*c)[3][4];
	char  *x[5];
	char (*y)[5];
	char **test[3][4];
	char (**magic)[3][2];
	printf("%d %c %lx\n", sizeof(test), test, test+1);
	// 96
	printf("%d %c\n", sizeof(magic), magic);
	//                                 char ** (*)[4]
	printf("%lx, %lx, %lx, %lx\n", a+1 ,       a,           *a,    **a);
	//                            char (*)[4], char (*)[4], char*, int  
	/*
	  the * operator give the last [] out , and & add the last [] up
	*/
	printf("%c, %lx, %lx, %lx\n", &a ,            a[0],   &a[0],       &a[0][0]);
	//                            char (*)[3][4], char *, char (*)[4], char* 
	printf("%lx, %lx, %lx, %lx, %lx\n", b+1 ,       b, *b,      **b,   ***b);
	//                                  char * (*)[4], char **, char*, int
	printf("%c, %lx, %lx, %lx\n", c+1 , c,        *c,          **c);
	//                            char (*)[3][4], char (*)[4], char *
	printf("%lx, %lx\n", x+1 , x);
	printf("%lx, %lx\n", y+1 , y);
	return 0;
}
