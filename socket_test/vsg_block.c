#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <string.h>
#include <sys/types.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <errno.h>

#define ETH_P_IP    0x0800

#define MAX_ETH     8
#define ETH_NAME_LEN    8

typedef struct _RAW_ETH {
    int8_t eth_name[ETH_NAME_LEN];
        int32_t raw_sock;
        } RAW_ETH;

        typedef struct _block_handle {
            int32_t eth_num;    //¿¿¿¿¿¿¿¿¿
                RAW_ETH raw_eth[MAX_ETH];   //¿¿¿¿¿¿
                } block_handle;

                block_handle *init_block(u_int8_t * eth_Name, int32_t len);
                int32_t block_tcp(block_handle * bhd,  void* blk_pkt);
                int32_t clean_block(block_handle * bhd);

#define NIPQUAD(addr) \
        ((unsigned char *)&addr)[0], \
    ((unsigned char *)&addr)[1], \
    ((unsigned char *)&addr)[2], \
    ((unsigned char *)&addr)[3]
#define NIPQUAD_FMT "%u.%u.%u.%u"

int32_t error_log(void)
{
	return 0;
}

u_int8_t *find_eth(u_int8_t * haystack)
{
	u_int8_t *needle = NULL;

	if (NULL == haystack) {
		goto ret;
	}

	needle = haystack;

	while (*needle) {
		if (0 == strncasecmp((char *) needle, "eth", strlen("eth"))
		    && needle[3] >= '0' && needle[3] <= '9') {
			goto ret;
		}

		needle++;
	};

	needle = NULL;
      ret:
	return needle;
}

u_int32_t get_eth_num(int8_t * eth_name)
{
	int32_t name_len = 0;
	int32_t number = 0;

	if (NULL == eth_name) {
		return 10000;
	}

	name_len = strlen((char *) eth_name);
	if (4 == name_len) {	//for the eth number is less than 10.
		if (eth_name[3] < '0' || eth_name[3] > '9') {
			return 10000;
		}
	} else if (5 == name_len) {	//for the eth number is 10 or more than 10.
		if (eth_name[3] < '0' || eth_name[3] > '9' || eth_name[4] < '0' || eth_name[4] > '9') {

			return 10000;
		}
	} else {		//only eth*(name_len=4) and eth**(name_len=5) are supportable.
		return 10000;
	}

	number = atoi((char *) (eth_name + 3));
	if (number >= 0) {
		return number;
	} else {
		return 10000;
	}
}

block_handle *init_block(u_int8_t * eth_Name, int32_t len)
{
	int32_t packet_socket = -1;
	int32_t on = -1;
	struct ifreq ifr;
	block_handle *bhd = NULL;
	//u_int8_t buf[128] = { 0 };
	//u_int8_t *pos = buf;
	
	if (NULL == eth_Name || len < 1 || len > 127) {
		error_log();
        printf("debug 01\n");
		goto ret;
	//} else {
	//	vs_strncpy((char *)buf, sizeof(buf), (char *)eth_Name, len);
	}

	bhd = malloc(sizeof(block_handle));
	if (NULL == bhd) {
		error_log();
        printf("debug 02\n");
		goto ret;
	}

	memset(bhd, 0, sizeof(block_handle));

//	while ((pos = find_eth(pos))) {

		/********************************************************
		*	protocol defined in linux/if_ether.h		*
		*	ETH_P_LOOP	0x0060 Ethernet Loopback packet	*
		*	ETH_P_IP	0x0800 Internet Protocol packet	*
		*	ETH_P_ALL	0x0003 Every packet(be careful!)*
		*********************************************************/
		//packet_socket = socket(PF_PACKET, SOCK_RAW, htons(0x800));
		//packet_socket = socket(PF_PACKET, SOCK_PACKET, htons(0x800));
		packet_socket = socket(AF_INET, SOCK_PACKET, htons(0x03));
        printf(" packet_socket%d  err %d\n", packet_socket, errno);

		//packet_socket = socket(AF_PACKET,SOCK_RAW,ETH_P_IP);
		

		if (packet_socket < 0) {
            printf("debug 03\n");
			goto ret;
		}

		strncpy(ifr.ifr_name, (char *)eth_Name, len);
		//length of the ethn is 4
		on = ioctl(packet_socket, SIOCGIFINDEX, &ifr);
		/*ifr.ifr_flags |= IFF_PROMISC + IFF_LOOPBACK + IFF_DEBUG;
		   ifr.ifr_flags |= IFF_PROMISC;
		   on = ioctl( packet_socket, SIOCSIFFLAGS, &ifr ); *//* set flags */
		if (fcntl(packet_socket, F_SETFL, O_NONBLOCK) < 0) {
            printf("debug 04\n");
					goto ret;
		}
#if 0
       	struct sockaddr_ll sll;
	 memset (&sll, 0, sizeof(sll));
	 sll.sll_family = AF_PACKET;
	 sll.sll_protocol = htons (ETH_P_IP);
	 sll.sll_ifindex = ifr.ifr_ifindex;
	 on = bind (packet_socket, (struct sockaddr *)&sll, sizeof(sll));
     printf("on %d error %d\n", on, errno);
	 if(on <= 0)
	 {	
		char buf1[256] = {0};
		FILE * fd1 = NULL;
		fd1 = fopen("./bhd1.log", "a+");
		snprintf(buf1,256, "1 fail\n");
		fwrite(buf1,sizeof(buf1),1,fd1);
		fclose(fd1);
        printf("debug 05\n");
		goto ret;
	 }
     #endif


		strncpy((char *)(bhd->raw_eth[0]).eth_name,  (char *)eth_Name, 4);
		(bhd->raw_eth[0]).raw_sock = packet_socket;
	


		//pos += 4;
//	};

      ret:
	if (packet_socket >= 0) {
		//close(packet_socket);
	}
	return bhd;
}

int32_t kill_send(int32_t kill_sock, int8_t * eth_name, u_int8_t * aBuf, int32_t aNum)
/********************************************************
*       ÊäÈë:   aFd:    ÍøÂç½Ó¿Ú±êÖ¾×Ö                  *
*               aBuf:   »º³åÇøµØÖ·                      *
*               aNum:   »º³åÇø³¤¶È                      *
*       ·µ»Ø:           ·¢ËÍÊý¾Ý³¤¶È                    *
*               -1:     ·¢ËÍ´íÎó                        *
*********************************************************/
{
	int32_t n = 0;
	struct sockaddr to;

	//int i;
	//printf("send[%d]=[",aNum);
	//for (i=0;i<aNum;i++)
	//      printf("%02X.",aBuf[i]);
	//printf("]\n");
	//printf("%s\n.",eth_name);

	strncpy((char *)to.sa_data,  (char *)eth_name, 14);
	
	n = sendto(kill_sock, aBuf, aNum, 0, &to, sizeof(to));
    
	
        printf("[%s %d ], socket errno %d, kill_sock %d, abuf %s, anum %d\n", __func__, __LINE__,errno,kill_sock,aBuf,aNum);
	if (n <= 0) {
        printf("[%s %d ], error socket errno %d, kill_sock %d, abuf %s, anum %d\n", __func__, __LINE__,errno,kill_sock,aBuf,aNum);
		error_log();
	}

/*	strncpy(to.sa_data,"eth1",14);
	n = sendto(kill_sock2,aBuf,aNum,0,&to,sizeof(to));
	if (n <= 0)
	printf_error("dt_ERROR2::Raw_Send: "); */

	return n;
}

u_int16_t Checksum(u_int16_t * buffer, int32_t size)
{
	u_int32_t cksum = 0;

	while (size > 1) {
		cksum += *buffer++;
		size -= sizeof(u_int16_t);
	}

	if (size) {
		cksum += *(u_int8_t *) buffer;
	}

	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);

	return (u_int16_t) (~cksum);
}

u_int16_t tcp_cksum(struct iphdr * ip, struct tcphdr * tcp, int32_t tcp_len)
{
	struct pseudo_header {	/* for TCP_CHECK_SUM */
		u_int32_t source_address;
		u_int32_t dest_address;
		u_int8_t placeholder;
		u_int8_t protocol;
		u_int16_t tcp_length;
		// Modified by ljb 2007.06.14
		u_int8_t tcp_data[64];
	} pseudo_header;

	register u_int16_t answer = 0;

	/* set the pseudo header fields */
	pseudo_header.source_address = ip->saddr;
	pseudo_header.dest_address = ip->daddr;
	pseudo_header.placeholder = 0;
	pseudo_header.protocol = IPPROTO_TCP;
	pseudo_header.tcp_length = htons(tcp_len);

	bcopy((int8_t *) tcp, (int8_t *) & pseudo_header.tcp_data, tcp_len);
	//pseudo_head:12
	answer = Checksum((u_int16_t *) & pseudo_header, 12 + tcp_len);

	return (answer);
}

int32_t block_tcp(block_handle * bhd, void * blk_pkt)
//u_int8_t *aData, int32_t aLengt
{
	u_int8_t buf[128] = { 0 };
	// mod for utm-arm by ljb 2007-03-30
	u_int8_t *bufplus2 = buf + 2;
	u_int8_t tmp_mac[10] = { 0 };
	int32_t t_ip_hlen = 0;
	int32_t t_ip_len = 0;
	struct iphdr *ip = NULL;
	struct tcphdr *tcp = NULL;
	int32_t ret_s = 0;
	//int32_t i = 0;
	//int32_t j = 0;
	u_int32_t tmp_ip = 0;
	u_int32_t back_seq = 0;
	u_int32_t back_ack = 0;
	u_int16_t tmp_port = 0;
	int32_t vlan_off = 0;
//	struct vs_skb *skb = blk_pkt->skb;
	

#define BLOCK_PACKET_HEADER_SIZE 60

	//memset(buf, 0, sizeof(buf));
	// mod for utm-arm by ljb 2007-03-30
	memcpy(bufplus2,  blk_pkt, 18);

	if ((0x81 == bufplus2[12]) && (0x00 == bufplus2[13]))	// VLAN Trunck tag
	{
		vlan_off = 4;
		ip = (struct iphdr *) (bufplus2 + 18);
		//t_ip_hlen = ip->ihl * 4;
		//t_ip_len = ntohs(ip->tot_len) - t_ip_hlen;
		tcp = (struct tcphdr *) (bufplus2 + 18 + sizeof(struct iphdr));
	} else {
		memset(bufplus2 + 14, 0, 4);
		ip = (struct iphdr *) (bufplus2 + 14);
		//t_ip_hlen = ip->ihl * 4;
		//t_ip_len = ntohs(ip->tot_len) - t_ip_hlen;
		tcp = (struct tcphdr *) (bufplus2 + 14 + sizeof(struct iphdr));
	}

	//ip head length
	t_ip_hlen = 20;
	//ip payload length
	t_ip_len = 20;

	tcp->source = 1;
	tcp->dest = 2;
	tcp->seq = 2222;
	tcp->ack_seq = 3333;
	//tcp head length, fixed 20.
	tcp->doff = 0x05;
	tcp->rst = 1;
	tcp->fin = 0;
	tcp->ack = 1;
	tcp->window = 1555;

	back_seq = tcp->ack_seq;
	back_ack = tcp->seq;
	//back_ack = htonl((ntohl(tcp->seq ) + t_ip_len - tcp->doff * 4));
	//tcp->seq = htonl((ntohl(tcp->seq ) + t_ip_len - tcp->doff*4 ));
	//tcp->seq = htonl( ntohl(tcp->seq) + (t_ip_len-tcp->doff*4) + (tcp->syn ? 1 : 0));

	ip->version = 0x04;	//fixed
	ip->ihl = 0x05;		//ip head length, fixed 20
	ip->tos = 0x0;		//fixed
	ip->tot_len = htons(40);	//ip payload length, fixed 40
	//ip->id = htons(0xFFFF);
	ip->id = htons(ntohs( 44+ 1));
	ip->frag_off = htons(0x4000);	//no fragment
	//ip->frag_off = htons(0x0000); //fragment, last frag
	ip->ttl = 0x80;		//128 hop, fixed
	ip->protocol = 0x06;	//TCP protocol
	ip->saddr = 0x1010101;
	ip->daddr = 0x01010102;
	// Modified by ljb 2007.06.14   
	tcp->check = 0;
	tcp->check = tcp_cksum(ip, tcp, t_ip_len);

	ip->check = 0;
	ip->check = Checksum((u_int16_t *) ip, t_ip_hlen);

	//printf("tcp->seq[%ld]tcp->doff[%d]ip->ihl[%d]\n",(long int)ntohl(tcp->seq), tcp->doff, ip->ihl);

//	for (i = 0; i <= bhd->eth_num; i++) {
#if 0	
		if ((bhd->raw_eth[i]).raw_sock <= 0 || (bhd->raw_eth[i]).eth_name!="eth0") {

			continue;
		}
#endif
	//	for (j = 0; j < 1; j++) {
			//ret_s = kill_send((bhd->raw_eth[i]).raw_sock, (bhd->raw_eth[i]).eth_name, bufplus2, BLOCK_PACKET_HEADER_SIZE);	//blk_pkt->raw_pkt_len);
			strncpy((char *)(bhd->raw_eth[0]).eth_name, "enp2s0", strlen("enp2s0"));

            printf("[%s %d], original src :%u.%u.%u.%u:%hu -->dst :%u.%u.%u.%u:%hu,syn %i, ack %i, fin %i, rst %i, tcp-seq:%u, ack %u\n",__func__,__LINE__,
                                        NIPQUAD(ip->saddr),ntohs(tcp->source),NIPQUAD(ip->daddr),ntohs(tcp->dest),
                                                                tcp->syn,tcp->ack,tcp->fin,tcp->rst,ntohl(tcp->seq), ntohl(tcp->ack_seq));

			ret_s = kill_send((bhd->raw_eth[0]).raw_sock,(bhd->raw_eth[0]).eth_name , bufplus2, BLOCK_PACKET_HEADER_SIZE);	
	//	}
//	}

/*	fprintf(stderr, "forward kill---[%d.%d.%d.%d : %d---->%d.%d.%d.%d : %d] t_ip_len[%d] rst[%d]\n",
		bufplus2[14+vlan_off+12],bufplus2[14+vlan_off+13],bufplus2[14+vlan_off+14],bufplus2[14+vlan_off+15], ntohs(tcp->source),
		bufplus2[14+vlan_off+16],bufplus2[14+vlan_off+17],bufplus2[14+vlan_off+18],bufplus2[14+vlan_off+19], ntohs(tcp->dest), t_ip_len,tcp->rst);
	
*/
	// ·´Ïò×è¶Ï
	memcpy(tmp_mac,  bufplus2, 6);
	memcpy(&bufplus2[0],  &bufplus2[6], 6);
	memcpy(&bufplus2[6],  tmp_mac, 6);

	tmp_ip = ip->saddr;
	ip->saddr = ip->daddr;
	ip->daddr = tmp_ip;

	tmp_port = tcp->source;
	tcp->source = tcp->dest;
	tcp->dest = tmp_port;

	tcp->rst = 1;
	tcp->fin = 0;
	tcp->ack = 1;

	tcp->seq = back_seq;
	tcp->ack_seq = back_ack;
	tcp->check = 0;
	tcp->check = tcp_cksum(ip, tcp, t_ip_len);

	ip->check = 0;
	ip->check = Checksum((u_int16_t *) ip, t_ip_hlen);

//	for (i = 0; i <= bhd->eth_num; i++) {
#if 0	
		if ((bhd->raw_eth[i]).raw_sock <= 0 || nic_in != get_eth_num((bhd->raw_eth[i]).eth_name)) {
			continue;
		}
#endif
	//	for (j = 0; j < 1; j++) {
			strncpy((char *)(bhd->raw_eth[0]).eth_name,"enp2s0", strlen("enp2s0"));
	
    printf("[%s %d], reply src :%u.%u.%u.%u:%hu -->dst :%u.%u.%u.%u:%hu,syn %i, ack %i, fin %i, rst %i, tcp-seq:%u, ack %u\n",__func__,__LINE__,
                        NIPQUAD(ip->saddr),ntohs(tcp->source),NIPQUAD(ip->daddr),ntohs(tcp->dest),
                                            tcp->syn,tcp->ack,tcp->fin,tcp->rst,ntohl(tcp->seq), ntohl(tcp->ack_seq));
			ret_s = kill_send((bhd->raw_eth[0]).raw_sock,(bhd->raw_eth[0]).eth_name, bufplus2, BLOCK_PACKET_HEADER_SIZE);	//blk_pkt->raw_pkt_len);
	//	}
//	}

/*	fprintf(stderr, "backward kill---[%d.%d.%d.%d : %d---->%d.%d.%d.%d : %d] t_ip_len[%d] rst[%d] \n",
		bufplus2[14+vlan_off+12],bufplus2[14+vlan_off+13],bufplus2[14+vlan_off+14],bufplus2[14+vlan_off+15], ntohs(tcp->source),
		bufplus2[14+vlan_off+16],bufplus2[14+vlan_off+17],bufplus2[14+vlan_off+18],bufplus2[14+vlan_off+19], ntohs(tcp->dest), t_ip_len,tcp->rst);
*/
	return ret_s;
}

int32_t clean_block(block_handle * bhd)
{
	if (bhd != NULL) {
		free(bhd);
		bhd = NULL;
	}

	return 0;
}

#if 1
int main(int argc, char **argv)
{
	int32_t retval = -1;
	int32_t handle = -1;
	int32_t nread = -1;
	int8_t buffer[1600] =
      {0x5c, 0x50, 0x15, 0xf0, 0xcb, 0x47,
       0x00, 0x0c, 0x29, 0xda, 0xc2, 0xcc,
       0x08, 0x00,
       0x00};
    
	char* blk_pkt;

	blk_pkt = buffer;
	block_handle *bhd = init_block("enp2s0", 10);
    block_tcp(bhd, blk_pkt);




	return 0;
}
#endif
