// gcc -O2
int a;
int main()
{
#if 0
	int b;
	a = 1;
	b = a;
	return b;
#endif
#if 0
	int b;
	a = 1;
	 __asm__ __volatile__ ("" : : : "memory");
	b = a;
	return b;
#endif
#if 0
#define ACCESS_ONCE(x)      (*(__volatile__  __typeof__(x) *)&(x))
	int b;
	a = 1;
	b = ACCESS_ONCE(a);
	return b;
#endif
#if 0
	int b;
	a = 1;
	__asm__ __volatile__ ("mfence":::"memory");
	b = a;
	return b;
#endif
#if 0
	int b;
	a = 1;
	__asm__ __volatile__ ("lfence":::"memory");
	b = a;
	return b;
#endif
#if 0
	int b;
	a = 1;
	__asm__ __volatile__ ("sfence":::"memory");
	b = a;
	return b;
#endif
#if 1
	int b;
	a = 1;
	__asm__ __volatile__ ("lock; addl $0,0(%%esp)":::"memory");
	b = a;
	return b;
#endif

	
}
