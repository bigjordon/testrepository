#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int glob=6;
int main()
{

	int var;
	pid_t p;
	var=88;
	printf("before vfork\n");

	printf("pid= %ld, var= %d, glob=%d\n",(long)getpid(),var,glob);
	if((p=vfork())<0)
	{
		printf("error");
	}
	else if(p==0)
	{
		printf("after fork enter child process branch\n");
		glob++;
		var++;
		printf("pid= %ld, var= %d , glob=%d\n",(long)getpid(),var,glob);
		close(1);
		printf("after fork leave child process branch\n");
		while (1)
		{
			sleep(1);
			var ++;
			var *= var;
			printf("%d\n", var);
		}
		_exit(0);
	}
	sleep(1);
	
	printf("after fork enter parent process branch\n");

	printf("pid= %ld, var= %d, glob=%d\n",(long)getpid(),var,glob);

	printf("after fork leave parent process branch\n");
		

	exit(0);

}

