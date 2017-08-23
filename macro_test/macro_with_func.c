#include <stdio.h>
#define DO_SOME(A, B) do { \
			int a, b, c; \
			 A + 1; \
			} while(0)
int func(void)
{
	printf("aaaaaa\n");
	return 0;
}


int main(void)
{
	DO_SOME(6, func);
	return 0;
}
/**
 * yes func never be called;
 */
