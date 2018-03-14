#include <stdio.h>
#include <stdlib.h>

int a = 1000000;
int b = 0, c;

static inline void add_a(void)
{
	a++;
}

int main()
{	
	int i = 0;
	for(i=0; i<1000000; ++i) {
		b++;
		c=b;
		a--;
		add_a();
		
	} 
	printf("a: %d\n",a);
	return 0;
}
