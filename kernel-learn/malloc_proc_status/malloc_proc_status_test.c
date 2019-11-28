// void *malloc(size_t size);

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *ap[1000];
    sleep(3);
    printf("start\n");
    int i = 0;
    while (i++ < 1000) {
        char * a  = malloc(10*1024);
        memset(a, 1, 10*1024);
        ap[i-1] = a;
        if (i%100 == 0){
            sleep(3);
        }
    }
    i = 0;
    printf("freee one!\n");
    //while (i++ < 800) {
    while (i++ < 1000) {
        free(ap[i-1]);
        if (i%100 ==0) {
            //sleep(4);
            }
    }
    while (1)
        sleep(1);
}
