#include <stdio.h>
#include <stdlib.h>
static  __attribute__((constructor(102))) void before6()
{

    printf("before6\n");
}

static  __attribute__((constructor(102))) void before2()
{

    printf("before2\n");
}
static  __attribute__((constructor(102))) void before4()
{

    printf("before4\n");
}
static  __attribute__((constructor(102))) void before5()
{

    printf("before5\n");
}
static  __attribute__((constructor(101))) void before1()
{

    printf("before1\n");
}

int main()
{
	printf("do main\n");
}
 /* if constructor has no propity arg the sequence may determined by the compile sequence, the function pre will
  called first*/
