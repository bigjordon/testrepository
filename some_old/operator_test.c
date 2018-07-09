#include <stdio.h>

int main()
{
	printf("%x\n", (0x100010bf ^ 0x0090819f & ~0xff0L));
	printf("%x\n", ((0x100010bf ^ 0x0090819f) & ~0xff0L));
	printf("%x\n", (0x100010bf ^ (0x0090819f & ~0xff0L)));
	return 0;
}
