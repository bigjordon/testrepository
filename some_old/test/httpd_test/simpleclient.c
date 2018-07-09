#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
 int sockfd;
 int len;
 struct sockaddr_in address;
 int result;
 #define LEN 200
 char ch[LEN];

 memset(ch , 0, sizeof(ch));
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 address.sin_family = AF_INET;
 address.sin_addr.s_addr = inet_addr("127.0.0.1");
 /*
   �����ȷִ�н�����һ���޷��ų�����������
   ���������ַ�������һ���Ϸ���IP��ַ��������INADDR_NONE
 */
 //address.sin_port = htons(9734);//�������ֽ�˳��ת��Ϊ�����ֽ�˳��
 address.sin_port = htons(45600);//�������ֽ�˳��ת��Ϊ�����ֽ�˳��
 len = sizeof(address);
 result = connect(sockfd, (struct sockaddr *)&address, len);
 if (result == -1)
 {
  perror("oops: client1");
  exit(1);
 }
 memcpy(ch, "i love mengmeng", strlen("i love mengmeng"));
 write(sockfd, ch, sizeof(ch));
 read(sockfd, ch, LEN);
 printf("char from server = %c\n", ch);
 close(sockfd);
 exit(0);
}
