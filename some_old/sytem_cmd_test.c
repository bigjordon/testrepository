#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argv[1][0] == 'a'){
		system("/venus_dt/guish");
	} else if (argv[1][0] == 'b'){
		system("/venus_dt/guish 0>/dev/null 1>/dev/null 2>/dev/null &");
	} else if (argv[1][0] == 'c'){
		system("./venus_dt/guish 0>/dev/null 1>/dev/null 2>/dev/null &");
	} else if (argv[1][0] == 'd'){
		system("/doc/venus_dt/conf/ttt -1");
	}
	return 0;
}
