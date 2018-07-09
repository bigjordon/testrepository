#define _XOPEN_SOURCE
#include <stdio.h>
#include <unistd.h>
//gcc -lcrypt passwd_test.c 
int main()
{
	char *p0 = NULL;
	char *pass1 = "hwlypaqdtk!";
	char *pass2 = "d.lovelife"; // wag
	char *pass3 = "s.lovelife";
	char *pass4 = "venus.term";
	char *pass5 = "RZX_Jsw!1hst@419"; // 任子行 ren zi hang key
	char *pass6 = "Jsw!1hst@419"; // ips trunck 
	char *pass7 = "hwlypaqdtk!go0117"; // wag trunck 
	char *out = NULL;
	out = crypt(pass1,"$5$2$");
	printf("pass1: %25s, encry: %s\n", pass1, out);
	out = crypt(pass2,"$5$QIM$");
	printf("pass2: %25s, encry: %s\n", pass2, out);
	out = crypt(pass3,"$6$.Q.I.M.$");
	printf("pass3: %25s, encry: %s\n", pass3, out);
	out = crypt(pass4,"$6$.Q.I.M.$");
	printf("pass4: %25s, encry: %s\n", pass4, out);
	out = crypt(pass5,"$6$.Q.I.M.$");
	printf("RXZ pass5: %21s, encry: %s\n", pass5, out);
	out = crypt(pass6,"$6$.Q.I.M.$");
	printf("ips trunck pass6: %14s, encry: %s\n", pass6, out);
	out = crypt(pass7,"$5$.Q.I.M.$");
	printf("wag trunck pass7: %14s, encry: %s\n", pass7, out);
	return 0;
}
