#include <stdio.h>
struct {
	int a:3;
	int b:4;
	int c:1;
	int foo;
} foo_abc = {0};
struct {
	int x:1, y:2, z:2;
	int bar;
} bar_xyz = {0};


int main()
{
	foo_abc.a = 7;
	foo_abc.b = 3;
	foo_abc.c = 1;

/*
	since a, b, c are all unsigned int bit domin
	then a use 3 bits, so then most improtant bit means the sign bit(positive or negtive)
	the other 2 bits are number bits

	b, c same as a

	so foo_abc.a =7 will be -1



*/


#if 1
	if (foo_abc.a == 7)
	printf("a: %d, b: %d, c: %d; foo: %d\n", foo_abc.a, foo_abc.b, foo_abc.c, foo_abc.foo);

	memset(&foo_abc, 0, sizeof(foo_abc));

	foo_abc.a = 10;
	foo_abc.b = 10;
	foo_abc.c = 10;
/*
	gcc test: if give more bits to a, b or c 
	then will ignore the overflow bits
	eg: a use 3 bits but 10d(1010b)use 4 bis ,the most important bit that 1 will be ignord
	    a will only be 3
*/
	printf("a: %d, b: %d, c: %d; foo: %d\n", foo_abc.a, foo_abc.b, foo_abc.c, foo_abc.foo);

	bar_xyz.x = 1;
	bar_xyz.y = 0;
	bar_xyz.z = 3;
	printf("d: %d, y: %d, z: %d; bar: %d\n", bar_xyz.x, bar_xyz.y, bar_xyz.z, bar_xyz.bar);
#endif

	return 0;
}
