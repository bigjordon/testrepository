// void *malloc(size_t size);

#include <stdio.h>
#include <stdlib.h>

int main()
{
    sleep(3);
    printf("start\n");
    while (1) {
        char * a  = malloc(10*1024*1024);
        sleep(5);
        printf("one !\n");
    }
}
