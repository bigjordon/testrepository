#include <stdio.h>
#include <stdlib.h>

#define AA(a, b, c)  int aa(int a, int b, int c =1) \
{ \
	printf("%d %d %d \n" , a, b ,c); \
	return 0; \
}
int bb (int a, int b, int c=1)
{
	int z = a+b+c;
	printf("sum is %d\n", z);
	return 0;
}
int main()
{
	
	bb(3,6);
	return 0;
}

