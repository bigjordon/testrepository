/* cli.cpp  -  Minimal ssleay client for Unix
   30.9.1996, Sampo Kellomaki <sampo@iki.fi> */

/* mangled to work with SSLeay-0.9.0b and OpenSSL 0.9.2b
   Simplified to be even more minimal
   12/98 - 4/99 Wade Scholine <wades@mail.cybg.com> */

#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


#define CHK_NULL(x) do {if ((x)==NULL) {printf("line: %d\n", __LINE__); exit (1); }} while(0)
#define CHK_ERR(err,s) if ((err)==-1) { perror(s); printf("line: %d\n", __LINE__); exit(1); }
#define CHK_SSL(err) if ((err)==-1) { ERR_print_errors_fp(stderr); printf("line: %d\n", __LINE__);  exit(2); }

int main (int argc, char **argv)
{
  int err;
  int sd;
  int ipversion6 = 0;
  struct sockaddr_in sa;
  struct sockaddr_in6 sa6;
  SSL_CTX* ctx;
  SSL*     ssl;
  X509*    server_cert;
  char*    str;
  char     buf [4096];
  const SSL_METHOD *meth;

  if (argc == 2) {
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "h") == 0) {
        printf("`client.bin 4 V4ADDR` use ipv4 client\n ");
        printf("`client.bin 6 V6ADDR` use ipv6 client\n");
        printf("`client.bin (h | -h)` print this help\n");
        return 0;
    } else {
        printf ("Ivalid argument\n\n");
        printf("`client.bin 4 V4ADDR` use ipv4 client\n ");
        printf("`client.bin 6 V6ADDR` use ipv6 client\n");
        printf("`client.bin (h | -h)` print this help\n");
        return 0;
    }
  } else if (argc == 3) {
        if (atoi(argv[1]) == 6) {
            ipversion6 = 1;
        }
  } else {
        printf ("Ivalid argument\n\n");
        printf("`client.bin 4 V4ADDR` use ipv4 client\n ");
        printf("`client.bin 6 V6ADDR` use ipv6 client\n");
        printf("`client.bin (h | -h)` print this help\n");
        return 0;
  }

  SSLeay_add_ssl_algorithms();
  //meth = SSLv3_client_method(); openssl v2 not support in 1.0.2o now
  meth = TLSv1_2_client_method();
  SSL_load_error_strings();
  ctx = SSL_CTX_new (meth);
  CHK_NULL(ctx);

  CHK_SSL(err);
  
  /* ----------------------------------------------- */
  /* Create a socket and connect to server using normal socket calls. */
  
  if (ipversion6) {
    sd = socket (AF_INET6, SOCK_STREAM, 0);       CHK_ERR(sd, "socket");
  } else {
    sd = socket (AF_INET, SOCK_STREAM, 0);       CHK_ERR(sd, "socket");
  }
 
  memset (&sa, '\0', sizeof(sa));
  memset (&sa6, '\0', sizeof(sa6));

  if (ipversion6) {
      sa6.sin6_family      = AF_INET6;
      inet_pton(AF_INET6, argv[2], &sa6.sin6_addr); /* Server IP*/
      sa6.sin6_port        = htons     (1111);          /* Server Port number */
      
      err = connect(sd, (struct sockaddr*) &sa6,
            sizeof(sa6));                   CHK_ERR(err, "connect");
  } else {
      sa.sin_family      = AF_INET;
      sa.sin_addr.s_addr = inet_addr (argv[2]);   /* Server IP */
      sa.sin_port        = htons     (1111);          /* Server Port number */
      
      err = connect(sd, (struct sockaddr*) &sa,
            sizeof(sa));                   CHK_ERR(err, "connect");
  }

  /* ----------------------------------------------- */
  /* Now we have TCP conncetion. Start SSL negotiation. */
  
  ssl = SSL_new (ctx);
  CHK_NULL(ssl);    
  SSL_set_fd (ssl, sd);
  err = SSL_connect (ssl);
  CHK_SSL(err);
    
  /* Following two steps are optional and not required for
     data exchange to be successful. */
  
  /* Get the cipher - opt */

  printf ("SSL connection using %s\n", SSL_get_cipher (ssl));
  
  /* Get server's certificate (note: beware of dynamic allocation) - opt */

  server_cert = SSL_get_peer_certificate (ssl);
  CHK_NULL(server_cert);
  printf ("Server certificate:\n");
  
  str = X509_NAME_oneline (X509_get_subject_name (server_cert),0,0);
  CHK_NULL(str);
  printf ("\t subject: %s\n", str);
  OPENSSL_free (str);

  str = X509_NAME_oneline (X509_get_issuer_name  (server_cert),0,0);
  CHK_NULL(str);
  printf ("\t issuer: %s\n", str);
  OPENSSL_free (str);

  /* We could do all sorts of certificate verification stuff here before
     deallocating the certificate. */

  X509_free (server_cert);
  
  /* --------------------------------------------------- */
  /* DATA EXCHANGE - Send a message and receive a reply. */

  err = SSL_write (ssl, "Hello World!", strlen("Hello World!"));  CHK_SSL(err);
  
  err = SSL_read (ssl, buf, sizeof(buf) - 1);                     CHK_SSL(err);
  buf[err] = '\0';
  printf ("Got %d chars:'%s'\n", err, buf);

  sleep(20);

  SSL_shutdown (ssl);  /* send SSL/TLS close_notify */

  /* Clean up. */

  close (sd);
  SSL_free (ssl);
  SSL_CTX_free (ctx);
  return 0;
}
/* EOF - cli.cpp */
