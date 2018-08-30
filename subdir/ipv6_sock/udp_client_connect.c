#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>

#define ERROR_DO printf("function: %s; line NO.: %d \
    error: %s \n", __FUNCTION__, __LINE__, strerror(errno))


#define PEERADDRSTR "2000:bb::58"
#define LOCLADDRSTR "2000:bb::56"
int start(int *serv_sock, int enable_connect)
{
    struct sockaddr_in6 local;                                                               
    struct sockaddr_in6 peer;                                                               
    int ret = 0;                                                                          
    int local_len = 0;                                                                      
    int peer_len = 0;                                                                      
    struct in6_addr localaddr;
    struct in6_addr peeraddr;
                                                                                          
    local_len = sizeof(struct sockaddr_in6);                                                 
    peer_len = local_len;                                                                    
                                                                                          
    memset(&local, 0, local_len);                                                             
    memset(&peer, 0, peer_len);                                                             
                                                                                          
    local.sin6_family = AF_INET6;                                                             
    peer.sin6_family = AF_INET6;                                                             
                                                                                          
    inet_pton(AF_INET6, PEERADDRSTR, &peeraddr);
    inet_pton(AF_INET6, LOCLADDRSTR, &localaddr);
    local.sin6_addr = localaddr ;                                      
    peer.sin6_addr = peeraddr ;                                     
                                                                                                
    local.sin6_port = htons(1121);                     
    peer.sin6_port = htons(1111);                     
                                                                                                
    *serv_sock = socket(AF_INET6, SOCK_DGRAM, 0);                                                
    if(*serv_sock < 0){                                                                         
         ERROR_DO;
         printf("[HA UDP] sock init failed.error: %s\n", strerror(errno));       
            return -1;                                                                          
    }                                                                                           
                                                                                                
    /* set timeout */                                                                           
    struct timeval tv_out;                                                                      
    tv_out.tv_sec = 5;                                                                         
    tv_out.tv_usec = 0;                                                                         
    if(setsockopt(*serv_sock, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out)) < 0){           
            close(*serv_sock);                                                                  
            ERROR_DO;
            return -1;                                                                          
    }                                                                                           
    if(setsockopt(*serv_sock, SOL_SOCKET, SO_BINDTODEVICE, "enp4s0", strlen("enp4s0")+1) < 0){
         ERROR_DO;
         printf ("******please run with sudo or as root********\n");
        close(*serv_sock);                                                          
        exit(0);                                                                  
    }                                                                                   
                                                                                                
    int on = 1;                                                                                 
    if(setsockopt(*serv_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0){                  
            close(*serv_sock);                                                                  
         ERROR_DO;
            return -1;                                                                          
    }                                                                                           
                                                                                                
    int recv_buf = 10000000;                                                                    
    if(setsockopt(*serv_sock, SOL_SOCKET, SO_RCVBUF, (char *) &recv_buf, sizeof(recv_buf))< 0){ 
            close(*serv_sock);                                                                  
         ERROR_DO;
            return -1;                                                                          
    }                                                                                           
                                                                                                
    ret = bind(*serv_sock, (struct sockaddr *)&local, local_len);                                   
    if(ret < 0){
            close(*serv_sock);                                                                  
         ERROR_DO;
            return -1;                                                                      
    }                                                                                       
    if (enable_connect) {
        printf("enable udp connect\n");
        ret = connect(*serv_sock, (struct sockaddr *)&peer, local_len);                           
        if(ret < 0){                                                                            
                return -1;                                                                      
        }                                                                                       
    }
    return 0;                                                                               

}

int send6(void)
{
     int client_fd;
     struct sockaddr_in6 ser_addr;
     struct sockaddr_in6 cli_addr;

     struct in6_addr seraddr;
     struct in6_addr cliaddr;
    #define BUFF_LEN 20 
    char buf[20] = {"abc"}; 
     client_fd = socket(AF_INET6, SOCK_DGRAM, 0);
     if(client_fd < 0)
     {
         ERROR_DO;
         return -1;
     }
 
     memset(&ser_addr, 0, sizeof(ser_addr));
     memset(&cli_addr, 0, sizeof(ser_addr));

     inet_pton(AF_INET6, LOCLADDRSTR, &seraddr);
     inet_pton(AF_INET6, PEERADDRSTR, &cliaddr);
     ser_addr.sin6_family = AF_INET6;
     ser_addr.sin6_addr = seraddr;
     ser_addr.sin6_port = htons(1121);
    
     cli_addr.sin6_family = AF_INET6;
     cli_addr.sin6_addr = cliaddr;
     cli_addr.sin6_port = htons(1111);

     if (bind(client_fd, (struct sockaddr *)&cli_addr, sizeof(cli_addr)))
         ERROR_DO;

    sendto(client_fd, buf, BUFF_LEN, 0, (struct sockaddr*) &ser_addr, sizeof(ser_addr));
    close(client_fd);
    return 0;
}
int main(int argc, char **argv)                                                   
{                                                                                             
    enum {
        DISABLE_CONNECT,
        ENABLE_CONNECT
    };
    int sock;
    int len;
    char buff[256] = {0};
    start(&sock, DISABLE_CONNECT);
    while (1) {
        // no work very well
        send6();
        len = read(sock, buff, 256);
        if (len < 0)ERROR_DO;
        printf("len: %d %s\n", len, buff);
        sleep(3);
    }
    return 1;
}
