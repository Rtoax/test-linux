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


#define CERTSERVER "serverCert.cer"
#define KEYSERVER "serverKey.pem"

#define CHK_ERR(err, s) if((err) == -1) { perror(s); return -1; }
#define CHK_RV(rv, s) if((rv) != 1) { printf("%s error\n", s); return -1; }
#define CHK_NULL(x, s) if((x) == NULL) { printf("%s error\n", s); return -1; }
#define CHK_SSL(err, s) if((err) == -1) { ERR_print_errors_fp(stderr);  return -1;}

int main(void)
{
        int rv, err;
        SSL_CTX *ctx = NULL;
        const SSL_METHOD *meth = NULL;
        int listenfd;
        int accept_sd;
        struct sockaddr_in srvaddr;
        struct sockaddr_in cltaddr;
        socklen_t addrlen;
        SSL *ssl = NULL;
        char buf[4096];

        rv = SSL_library_init();
        CHK_RV(rv, "SSL_library_init");

        meth = DTLS_server_method();
        ctx = SSL_CTX_new(meth);
        CHK_NULL(ctx, "SSL_CTX_new");

        rv = SSL_CTX_use_certificate_file(ctx, CERTSERVER, SSL_FILETYPE_PEM);
        CHK_RV(rv, "SSL_CTX_use_certicificate_file");

        rv = SSL_CTX_use_PrivateKey_file(ctx, KEYSERVER, SSL_FILETYPE_PEM);
        CHK_RV(rv, "SSL_CTX_use_PrivateKey_file");

        rv = SSL_CTX_check_private_key(ctx);
        CHK_RV(rv, "SSL_CTX_check_private_key");

        listenfd = socket(AF_INET, SOCK_STREAM, 0);
        CHK_ERR(listenfd, "socket");
        memset(&srvaddr, 0, sizeof(srvaddr));
        srvaddr.sin_family = AF_INET;
        srvaddr.sin_port = htons(12345);
        srvaddr.sin_addr.s_addr = INADDR_ANY;

        err = bind(listenfd, (struct sockaddr *)&srvaddr,
                    sizeof(srvaddr));
        CHK_ERR(err, "bind");
        err = listen(listenfd, 5);
        CHK_ERR(err, "listen");

        addrlen = sizeof(cltaddr);
        accept_sd = accept(listenfd, (struct sockaddr *)&cltaddr, &addrlen);
        CHK_ERR(accept_sd, "accept");
        close(listenfd);
        printf("Connect to %s, port 0x%04X(=%d)\n",
                inet_ntoa(cltaddr.sin_addr),
                (int)ntohs(cltaddr.sin_port),
                (int)ntohs(cltaddr.sin_port));

        ssl = SSL_new(ctx);
        CHK_NULL(ssl, "SSL_new");
        rv = SSL_set_fd(ssl, accept_sd);
        CHK_RV(rv, "SSL_set_fd");
        rv = SSL_accept(ssl);
        CHK_RV(rv, "SSL_accpet");

        rv = SSL_read(ssl, buf, sizeof(buf) - 1);
        CHK_SSL(rv, "SSL_read");
        buf[rv] = '\0';
        printf("Got %d chars :%s\n", rv, buf);
        rv = SSL_write(ssl, "I accept your request", strlen("I accept your request"));
        CHK_SSL(rv, "SSL_write");

        close(accept_sd);
        SSL_free(ssl);
        SSL_CTX_free(ctx);

        return 0;
}

