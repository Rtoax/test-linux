#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 1024
#define CTRL_STREAM 0
#define DATA_STREAM 1

int sock;

void handle_signal(int signum)
{
	printf(" Cerrando...\n");
	if (close(sock) < 0)
		perror("close");
	exit(0);
}

int main(int argc, char **argv)
{
	int i = 0;
	int ret, flags;
	int addr_count;
	char address[16];
	char buffer[BUFFER_SIZE + 1];
	socklen_t addr_len;
	socklen_t hb_len;

	struct sockaddr_in addr;
	struct sctp_status status;
	struct sctp_initmsg initmsg;
	struct sctp_event_subscribe events;
	struct sigaction sig_handler;
	struct sctp_paddrparams heartbeat;
	struct sctp_rtoinfo rtoinfo;
	struct sctp_sndrcvinfo sndrcvinfo;
	struct sockaddr_in *paddrs[5];
	struct sockaddr_in server;

	/*memset(&buffer,	 '0', BUFFER_SIZE);*/
	memset(&initmsg,   0, sizeof(struct sctp_initmsg));
	memset(&addr,      0, sizeof(struct sockaddr_in));
	memset(&events,    0, sizeof(struct sctp_event_subscribe));
	memset(&status,    0, sizeof(struct sctp_status));
	memset(&heartbeat, 0, sizeof(struct sctp_paddrparams));
	memset(&rtoinfo,   0, sizeof(struct sctp_rtoinfo));

	addr_len = (socklen_t)sizeof(struct sockaddr_in);

	if (argc < 2 || (inet_addr(argv[1]) == -1))	{
		puts("usage: sctpc [IP address]");
		return 0;
	}

	strncpy(address, argv[1], 15);
	address[15] = 0;

	addr.sin_family = AF_INET;
	inet_aton(address, &(addr.sin_addr));
	addr.sin_port = htons(PORT);

	initmsg.sinit_num_ostreams = 2;
	initmsg.sinit_max_instreams = 2;
	initmsg.sinit_max_attempts = 1;

	heartbeat.spp_flags = SPP_HB_ENABLE;
	heartbeat.spp_hbinterval = 5000;
	heartbeat.spp_pathmaxrxt = 1;

	rtoinfo.srto_max = 2000;

	sig_handler.sa_handler = handle_signal;
	sig_handler.sa_flags = 0;

	/*Handle SIGINT in handle_signal Function*/
	if (sigaction(SIGINT, &sig_handler, NULL) == -1)
		perror("sigaction");

	/*Create the Socket*/
	if ((ret = (sock = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP))) < 0)
		perror("socket");

	/*Configure Heartbeats*/
	if ((ret = setsockopt(sock, SOL_SCTP, SCTP_PEER_ADDR_PARAMS,
			&heartbeat, sizeof(heartbeat))) < 0)
		perror("setsockopt");

	/*Set rto_max*/
	if ((ret = setsockopt(sock, SOL_SCTP, SCTP_RTOINFO,
			&rtoinfo, sizeof(rtoinfo))) < 0)
		perror("setsockopt");

	/*Set SCTP Init Message*/
	if ((ret = setsockopt(sock, SOL_SCTP, SCTP_INITMSG,
			&initmsg, sizeof(initmsg))) < 0)
		perror("setsockopt");

	/*Enable SCTP Events*/
	events.sctp_data_io_event = 1;
	events.sctp_association_event = 1;
	if ((ret = setsockopt(sock, SOL_SCTP, SCTP_EVENTS,
			(void *)&events, sizeof(events))) < 0)
		perror("setsockopt");

	/*Get And Print Heartbeat Interval*/
	hb_len = (socklen_t)(sizeof heartbeat);
	getsockopt(sock, SOL_SCTP, SCTP_PEER_ADDR_PARAMS, &heartbeat, &hb_len);
	/*printf("Heartbeat interval %d\n", heartbeat.spp_hbinterval);*/

	/*Connect to Host*/
	if (((ret = connect(sock, (struct sockaddr*)&addr,
			sizeof(struct sockaddr)))) < 0)	{
		perror("connect");
		close(sock);
		exit(0);
	}

	/*Get Peer Addresses*/
	addr_count = sctp_getpaddrs(sock, 0, (struct sockaddr**)paddrs);
	printf("# IP asociadas: %d\n", addr_count);
	for (i = 0; i < addr_count; i++)
		printf("  IP %d: %s\n", i+1, inet_ntoa((*paddrs)[i].sin_addr));
	sctp_freepaddrs((struct sockaddr*)*paddrs);

	/*Start to recv data*/
	while ((ret = sctp_recvmsg(sock, (void *)buffer, sizeof(buffer),
			(struct sockaddr *)&server, &addr_len, &sndrcvinfo, &flags)) > 0) {
		if (!(flags & MSG_NOTIFICATION)) {
			buffer[ret] = 0;
			if (sndrcvinfo.sinfo_stream == CTRL_STREAM) {
				printf("%s CTRL(%d): %s", inet_ntoa(server.sin_addr),
						sndrcvinfo.sinfo_stream, buffer);
			} else if (sndrcvinfo.sinfo_stream == DATA_STREAM) {
				printf("%s DATA(%d): %s", inet_ntoa(server.sin_addr),
						sndrcvinfo.sinfo_stream, buffer);
			}
		}
	}

	if (close(sock) < 0)
		perror("close");

	return 0;
}

