#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>



int main()
{
    void *addr2 = NULL;
    void * addr = mmap(NULL, 1000, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    *((int *)addr) = 4;
    addr2 = mmap(addr, 1000, PROT_READ , MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
    if (addr != addr2)
        printf("not equal\n");
    return 0;
}
