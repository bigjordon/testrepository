#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <linux/in.h>


int main()
{
	int cfd;
	struct sockaddr_in s_add;
	unsigned short portnum = 10000;
	printf("hell ....\n");
	cfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&s_add,sizeof(struct sockaddr));  
	s_add.sin_family=AF_INET;  
	s_add.sin_addr.s_addr= inet_addr("192.168.54.58");   
	s_add.sin_port=htons(portnum);
	while (1) {
		printf("sleep ....\n");
		sleep(3);
		if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr_in)))  
		{  
		    printf("connect fail !\r\n");  
		    return -1;  
		} 
	}
	
	return 0;
}
