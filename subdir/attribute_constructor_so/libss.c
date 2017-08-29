#include <stdio.h>  
#include <string.h>  
  
void print()   
{  
	printf("I am print\n");  
}  
     
int add(int a, int b)  
{  
    printf("Sum %d and %d is %d\n", a, b, a + b);  
    return 0;  
}  
//static void king() __attribute__((constructor(101))); the following is also right  
static __attribute__((constructor())) void king()  
{  
    printf("I am king\n");  
}  
