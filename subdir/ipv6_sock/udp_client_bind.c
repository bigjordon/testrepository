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
int start(void)
{
    int ssock;
    int *serv_sock = &ssock;
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
                                                                                          
    inet_pton(AF_INET6, "2000:bb::58", &peeraddr);
    inet_pton(AF_INET6, "2000:bb::56", &localaddr);
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
    tv_out.tv_sec = 15;                                                                         
    tv_out.tv_usec = 0;                                                                         
    if(setsockopt(*serv_sock, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out)) < 0){           
            close(*serv_sock);                                                                  
            ERROR_DO;
            return -1;                                                                          
    }                                                                                           
    if(setsockopt(*serv_sock, SOL_SOCKET, SO_BINDTODEVICE, "enp4s0", strlen("enp4s0")+1) < 0){
         ERROR_DO;
        close(*serv_sock);                                                          
        return -1;                                                                  
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
     ret = connect(*serv_sock, (struct sockaddr *)&peer, local_len);                           
    if(ret < 0){                                                                            
            return -1;                                                                      
    }                                                                                       
    return 0;                                                                               

}

int main(int *serv_sock)                                                   
{                                                                                             
    start();
    while (1) {
        sleep(10);
    }
    return 1;
}
