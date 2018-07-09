#include <stdio.h>
#include <stdlib.h>


int main()
{
	int a = 0x80;
	int mask0 = 0x1;
	int mask1 = 0x10;
	int mask2 = 0x20;

	printf("out: %s\n", a&(mask1 | mask2) ? "true": "false");
	return 0;
}
