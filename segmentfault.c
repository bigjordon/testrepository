#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char * a = (char *)strtoul(argv[1], NULL, 16);;
    *(a) = 5;
    return 1;
}
