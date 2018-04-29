// gcc -c test.c -o test -O2
char test(char *b){
	char *a = b;
volatile char c = *a;
	return c;
}
