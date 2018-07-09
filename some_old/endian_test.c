#include "endian.h"
#include "stdio.h"
int main()
{

#if __BYTE_ORDER == __BIG_ENDIAN
	printf("big is done!\n");
#elif __BYTE_ORDER == __LITTLE_ENDIAN
	printf("little is done!\n");
#endif
	return 0;
}
