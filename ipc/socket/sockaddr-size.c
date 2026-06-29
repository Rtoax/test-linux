#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netpacket/packet.h>   /* struct sockaddr_ll */
#include <sys/un.h>             /* unsocket head file */
#include <sys/types.h>
#include <unistd.h>             /* socket close will use */
#include <netinet/in.h>         /* htons/htonl*/

int main(void)
{
#define SIZEOF(s) printf("sizeof(%s) = %ld\n", #s, sizeof(s))
	SIZEOF(struct sockaddr_in);
	SIZEOF(struct sockaddr_ll);
	SIZEOF(struct sockaddr_un);
	SIZEOF(struct sockaddr_storage);
#undef SIZEOF
	return 0;
}
