// it seems that the all code can be realise by <<<inet_ntoa>>>
#include<stdio.h>
typedef unsigned char u8_t;
typedef unsigned int u32_t;
#define ip4_addr_get_u32(src_ipaddr) ((src_ipaddr)->addr)
struct ip_addr {
  u32_t addr;
};

typedef struct ip_addr ip_addr_t;
char *ipaddr_ntoa_r(const ip_addr_t *addr, char *buf, int buflen)
{
  u32_t s_addr;
  char inv[3];
  char *rp;
  u8_t *ap;
  u8_t rem;
  u8_t n;
  u8_t i;
  int len = 0;

  s_addr = ip4_addr_get_u32(addr);

  rp = buf;
  ap = (u8_t *)&s_addr;
  for(n = 0; n < 4; n++) {
    i = 0;
    do {
      rem = *ap % (u8_t)10;
      *ap /= (u8_t)10;
      inv[i++] = '0' + rem;
    } while(*ap);
    while(i--) {
      if (len++ >= buflen) {
        return NULL;
      }
      *rp++ = inv[i];
    }
    if (len++ >= buflen) {
      return NULL;
    }
    *rp++ = '.';
    ap++;
  }
  *--rp = 0;
  return buf;
}




char *
ipaddr_ntoa(const ip_addr_t *addr)
{
  static char str[16];
  return ipaddr_ntoa_r(addr, str, 16);
}


int main(int argc, char **argv)
{
	int t = atoi(argv[1]);
	printf("%s\n", ipaddr_ntoa((const struct ip_addr_t *)(&t)));
	return 1;
}
