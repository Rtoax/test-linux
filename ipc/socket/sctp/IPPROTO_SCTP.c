#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>


int main(void)
{
	int sctp_socket1 = socket(PF_INET, SOCK_STREAM, IPPROTO_SCTP);
	int sctp_socket2 = socket(PF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);

	printf("%d,%d\n", sctp_socket1, sctp_socket2);

	close(sctp_socket1);
	close(sctp_socket2);
	return 0;
}
