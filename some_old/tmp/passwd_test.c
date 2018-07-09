#define _XOPEN_SOURCE
#include <stdio.h>
#include <unistd.h>
#define FMT "%-8s: %-25s encry: %s\n"
//gcc -lcrypt passwd_test.c 
int main()
{
	char *pass1 = "tianshiMaimeili";
	char *pass2 = "tianshiMaimeili"; 
	char *pass3 = "tianshiMaimeili";
	char *pass4 = "tianshiMaimeili";
	char *pass5 = "tianshiMaimeili"; 
	char *pass6 = "tianshiMaileili"; 
	char *out = NULL;

	out = crypt(pass1,"zl");
	printf(FMT,"pass1", pass1, out);
	out = crypt(pass2,"lz");
	printf(FMT, "pass2", pass2, out);
	out = crypt(pass3,"$1$.zh.I.l.$");
	printf(FMT, "pass3", pass3, out);
	out = crypt(pass4,"$5$.zh.I.l.$");
	printf(FMT, "pass4", pass4, out);
	out = crypt(pass5,"$6$zhIl$");
	printf(FMT, "pass5", pass5, out);
	out = crypt(pass6,"$6$.zh.I.l.$");
	printf(FMT, "pass6",pass6, out);
	return 0;
}
