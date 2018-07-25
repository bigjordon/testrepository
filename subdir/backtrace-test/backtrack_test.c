#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void sigsem_exec(int sig)
{
int j, nptrs;
#define SIZE 100
    void *buffer[100];
    char **strings;
    printf("*********COMING HRER**************\n\n\n\n");
    nptrs = backtrace(buffer, SIZE);
    printf("backtrace() returned %d addresses\n", nptrs);

    /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
       would produce similar output to the following: */

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < nptrs; j++)
        printf("%s\n", strings[j]);

    free(strings);
    exit(sig);

}
typedef int (*aaa)(void);
void
myfunc3(void)
{
	aaa my = 0x44556677;
//	*((int*)(0)) = 5; // key line
	while (1) {
		my();
		sleep(1);
	}
}
static void   /* "static" means don't export the symbol... */
myfunc2(void)
{
    myfunc3();
}

void
myfunc(int ncalls)
{
    if (ncalls > 1)
        myfunc(ncalls - 1);
    else
        myfunc2();
}

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "%s num-calls\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    signal(SIGSEGV, sigsem_exec);
    myfunc(atoi(argv[1]));
    exit(EXIT_SUCCESS);
}

