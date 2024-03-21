#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>
#include <openssl/err.h>


#define CHK_ERR(err, s) if((err) == -1) { perror(s); return -1; }
#define CHK_RV(rv, s) if((rv) != 1) { printf("%s error\n", s); return -1; }
#define CHK_NULL(x, s) if((x) == NULL) { printf("%s error\n", s); return -1; }
#define CHK_SSL(err, s) if((err) == -1) { ERR_print_errors_fp(stderr);  return -1;}

int main(void)
{
        int rv;
        int err;
        int sockfd;
        struct sockaddr_in sockaddr;
        const SSL_METHOD *meth = NULL;
        SSL_CTX *ctx = NULL;
        SSL *ssl = NULL;
        char buf[4096];

        rv = SSL_library_init();
        CHK_RV(rv, "SSL_library_init");

        meth = DTLS_client_method();
        ctx = SSL_CTX_new(meth);
        CHK_NULL(ctx, "SSL_CTX_new");

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        CHK_ERR(sockfd, "socket");

        memset(&sockaddr, 0, sizeof(sockaddr));
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_port = htons(12345);
        sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        err = connect(sockfd, (struct sockaddr *)&sockaddr,
                        sizeof(sockaddr));
        CHK_ERR(err, "connect");
        ssl = SSL_new(ctx);
        CHK_NULL(ssl, "SSL_new");
        rv = SSL_set_fd(ssl, sockfd);
        CHK_RV(rv, "SSL_set_fd");
        rv = SSL_connect(ssl);
        CHK_RV(rv, "SSL_connect");

        rv = SSL_write(ssl, "Hello, I am the client", strlen("Hello, I am the client"));
        CHK_SSL(rv, "SSL_write");
        rv = SSL_read(ssl, buf, sizeof(buf) - 1);
        CHK_SSL(rv, "SSL_read");
        buf[rv] = '\0';
        printf("Got %d chars :%s\n", rv, buf);

        SSL_shutdown(ssl);
        close(sockfd);
        SSL_free(ssl);
        SSL_CTX_free(ctx);

        return 0;
}

