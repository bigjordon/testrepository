#include <stdio.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <string.h>  
#include <sys/uio.h>  
  
int  main()  
{  
    struct iovec iov[3];  
    ssize_t nr;  
    int fd, i;  
  
    char *buf[] = {  
        "one   Just because you can do it, doesn't mean that you have to.\n",  
        "two   Just because you can do it, doesn't mean that you have to.\n",  
        "three Just because you can do it, doesn't mean that you have to.\n" };  
  
    fd = open("c++.txt", O_WRONLY | O_CREAT | O_TRUNC);  
    if (fd == -1) {  
        perror("open");  
    }  
  
    /* fill out therr iovec structures */  
    for (i = 0; i < 3; ++i) {  
        iov[i].iov_base = buf[i];  
        iov[i].iov_len  = strlen(buf[i]) + 1;  
    }  
  
    /* write a single call, write them all out */  
    nr = writev(fd, iov, 3);  
    if (nr != -1) {  
        perror("writev");  
        return 1;  
    }  
  
    if (close(fd)) {  
        perror("close");  
    }  
  
    return 0;  
} 
