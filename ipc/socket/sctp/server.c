#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <net/if.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 1024
#define CTRL_STREAM 0
#define DATA_STREAM 1

int sock, conSock;


void handle_signal(int signum)
{
	printf(" Cerrando...\n");
	if (close(conSock) < 0)
		perror("close");
	if (close(sock) < 0)
		perror("close");
	exit(0);
}

int main(void)
{
	int ret, i = 0;
	int reuse = 1;
	int addr_count = 0;
	char buffer[BUFFER_SIZE + 1];
	socklen_t addr_len;
	socklen_t hb_len;

	struct sockaddr_in addr;
	struct sockaddr_in *laddr[9];
	struct sctp_event_subscribe events;
	struct sctp_paddrparams heartbeat;
	struct sigaction sig_handler;
	struct sctp_rtoinfo rtoinfo;
	struct sockaddr_in client;

	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) < 0) {
		perror("socket");
		return 1;
	}

	memset(&addr,      0, sizeof(struct sockaddr_in));
	memset(&events,    0, sizeof(struct sctp_event_subscribe));
	memset(&heartbeat, 0, sizeof(struct sctp_paddrparams));
	memset(&rtoinfo,   0, sizeof(struct sctp_rtoinfo));

	addr_len = (socklen_t)sizeof(struct sockaddr_in);

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	sig_handler.sa_handler = handle_signal;
	sig_handler.sa_flags = 0;

	/* Heart beat */
	heartbeat.spp_flags = SPP_HB_ENABLE;
	heartbeat.spp_hbinterval = 5000;
	heartbeat.spp_pathmaxrxt = 1;

	/* Re-transmit time */
	rtoinfo.srto_max = 3000;

	 /*Set Signal Handler*/
	if(sigaction(SIGINT, &sig_handler, NULL) == -1)
		perror("sigaction");

	/*Set Heartbeats*/
	if(setsockopt(sock, SOL_SCTP, SCTP_PEER_ADDR_PARAMS,
			&heartbeat, sizeof(heartbeat)) != 0)
		perror("setsockopt");

	/*Set rto_max*/
	if(setsockopt(sock, SOL_SCTP, SCTP_RTOINFO,
			&rtoinfo, sizeof(rtoinfo)) < 0)
		perror("setsockopt");

	/*Set Events */
	events.sctp_data_io_event = 1;
	events.sctp_association_event = 1;
	if(setsockopt(sock, IPPROTO_SCTP, SCTP_EVENTS,
			&events, sizeof(events)) < 0)
		perror("setsockopt");

	/*Set the Reuse of Address*/
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
			&reuse, sizeof(int)) < 0)
		perror("setsockopt");

	/*Bind the Addresses*/
	if(bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0)
		perror("bind");

	if(listen(sock, 2) < 0)
		perror("listen");

	/*Get Heartbeat Value*/
	hb_len = (socklen_t)(sizeof heartbeat);
	getsockopt(sock, SOL_SCTP, SCTP_PEER_ADDR_PARAMS, &heartbeat, &hb_len);
	/*printf("Heartbeat interval %d\n", heartbeat.spp_hbinterval);*/

	/*Print Locally Binded Addresses*/
	/* Get all interfaces */
	addr_count = sctp_getladdrs(sock, 0, (struct sockaddr**)laddr);
	printf("# IP locales: %d\n", addr_count);
	for (i = 0; i < addr_count; i++)
		 printf("  IP %d: %s\n", i+1, inet_ntoa((*laddr)[i].sin_addr));
	sctp_freeladdrs((struct sockaddr*)*laddr);

	while (1) {
		i = 0;
		ret = 1;
		printf("# Esperando conexion\n");
		if ((conSock = accept(sock, (struct sockaddr *)&client, &addr_len)) == -1)
			perror("accept");
		printf("  Cliente: %s:%d\n", inet_ntoa(client.sin_addr), client.sin_port);
		while (ret > 0) {
			/* Send control message */
			snprintf(buffer, BUFFER_SIZE, "%s%02d\n", "control_", i);
			ret = sctp_sendmsg(conSock, (void *)buffer, (size_t)strlen(buffer),
					(struct sockaddr *)&client, addr_len, 0, 0,
					CTRL_STREAM, 0, 0);

			/* Send data message */
			snprintf(buffer, BUFFER_SIZE, "%s%02d\n", "data_", i);
			ret = sctp_sendmsg(conSock, (void *)buffer, (size_t)strlen(buffer),
					(struct sockaddr *)&client, addr_len, 0, 0,
					DATA_STREAM, 0, 0);

			/*printf("  Enviando a %s\n", inet_ntoa(client.sin_addr));*/
			i++;
			sleep(2);
		}
		/*close(conSock);*/
	}
	if (close(sock) < 0)
		perror("close");

	return 0;
}

