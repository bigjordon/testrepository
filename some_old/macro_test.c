#include <stdio.h>
#include <stdlib.h>
#define LWIP_DEBUGF(debug, message) do {aa message;} while(0)


void test_fun(int a, char *b)
{
	printf("time: %s\n \
		line: %d\n \
		func: %s\n \
		stdc: %d\n \
		stam: %s\n \
		file: %s\n",
		__TIME__, 
		__LINE__,
		__FUNCTION__,
		__STDC__, 
		__TIMESTAMP__, 
		__FILE__);
}

int main()
{
	LWIP_DEBUGF(tttt, ("ddd""sdsd", arg1, arg2));
	LWIP_DEBUGF(tttt, ("netconn_recv_data: received %p, len=%"U16_F"\n", buf, len));
	int a = 2;
	char *b = "test";
	test_fun(a, b);
	return 0;
}
