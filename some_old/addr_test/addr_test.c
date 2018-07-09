#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main(int argc, char **argv) 
{
	sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));

	addr inet_addr(argv[1]);
	return 0;
}

