#include <stdio.h>
int f(int a, int b)
{
	while(a+b > 0)
	{
	a = a+ 1;
	b = b -1;
	}
	return a+b;
}


int main1(int argc, char **argv)
{
	int i;
	for (i=0; i<argc; ++i) {
		printf("i: %d, %s\n", i, argv[i]);
	}
	printf("aaaa aaa aaaaaa");
	printf("11111aaaa aaa aaaaaa");
	printf("bbbbbbb\n");
	printf("%d\n", f(1, 0));
	
return 1;
}
int main(int argc, char **argv)
{
	int i;
	int j = 9;
	for (i = 0 ; i < 10000; ++i) {
		j = j * 9;
		if (j > 4445) {
			j = 9;
			i = 1;
		}
	}
	return 1;
}
