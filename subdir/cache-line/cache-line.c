#include <stdio.h>
#include <stdlib.h>


/* see cache line lenght using `cat /proc/cpuinfo` or other way*/
#define CACHE_LINE_LEN 1024*3

int step = 0;

/* allocate a big memory buffer */
#define BUFFER_LEN (1024*1024*1024)
int a[BUFFER_LEN] = {0};

int main(int argc, char **argv)
{
    int i, j = 0;
    int times = 10 * 10000;
    if (argc == 2) {
        step = atoi(argv[1]);
    } else {
        printf("need one arg, step number;\n");
        return 0;
    }    
    for (i = 0; i < times; ++i) {
        a[j] += 2;
        j += step;
        j = j% BUFFER_LEN;
    }
    return 0;
}
