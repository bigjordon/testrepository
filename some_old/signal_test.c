#include <signal.h>
#include <stdio.h>
#include <unistd.h>
int aaa = 1;
int ddd = 0;
int main()
{
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGCHLD);
	
	while (1) {
		if (aaa) {
			sigprocmask(SIG_BLOCK, &mask, NULL);
		}
		if (ddd) {
			sigprocmask(SIG_UNBLOCK, &mask, NULL);
		}
		printf("Hello start to sleep ...\n");
		sleep(1);
	}	
}
