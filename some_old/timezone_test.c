#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
int main()
{
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	printf("%d\n", tz.tz_minuteswest);
	return 0;
}
