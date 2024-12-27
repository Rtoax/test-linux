#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <net/if.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <linux/if_link.h>
#include <linux/if_xdp.h>
#include <poll.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>

#define XDP_FLAGS XDP_FLAGS_DRV_MODE
#define IFACE "eth0"

int main(int argc, char **argv)
{
	int sock_fd;
	struct sockaddr_xdp sxdp = {};
	struct xdp_umem_reg umem = {};
	struct xdp_mmap_offsets off;
	struct xdp_desc desc;
	void *bufs;
	int ret;
	socklen_t size;

	// Create XDP socket
	sock_fd = socket(AF_XDP, SOCK_RAW, 0);
	if (sock_fd < 0) {
		perror("socket");
		return -1;
	}

	// Set up XDP socket
	sxdp.sxdp_family = AF_XDP;
	sxdp.sxdp_ifindex = if_nametoindex(IFACE);
	if (sxdp.sxdp_ifindex == 0) {
		perror("if_nametoindex");
		close(sock_fd);
		return -1;
	}
	sxdp.sxdp_flags = XDP_FLAGS;

	ret = bind(sock_fd, (struct sockaddr *)&sxdp, sizeof(sxdp));
	if (ret) {
		perror("bind");
		close(sock_fd);
		return -1;
	}

	// Configure XDP UMEM (User Memory)
	umem.addr = (unsigned long)malloc(4096);
	if (!umem.addr) {
		perror("malloc");
		close(sock_fd);
		return -1;
	}
	umem.len = 4096;
	umem.chunk_size = 2048;
	umem.headroom = 0;

	ret = setsockopt(sock_fd, SOL_XDP, XDP_UMEM_REG, &umem, sizeof(umem));
	if (ret) {
		perror("setsockopt XDP_UMEM_REG");
		free((void *)umem.addr);
		close(sock_fd);
		return -1;
	}

	// Get mmap offsets
	size = sizeof(off);
	ret = getsockopt(sock_fd, SOL_XDP, XDP_MMAP_OFFSETS, &off, &size);
	if (ret) {
		perror("getsockopt XDP_MMAP_OFFSETS");
		free((void *)umem.addr);
		close(sock_fd);
		return -1;
	}

	// Map the UMEM
	bufs = mmap(NULL, umem.len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_LOCKED,
		    sock_fd, XDP_UMEM_PGOFF_FILL_RING);
	if (bufs == MAP_FAILED) {
		perror("mmap");
		free((void *)umem.addr);
		close(sock_fd);
		return -1;
	}

	// Poll the socket for incoming packets
	struct pollfd fds = { .fd = sock_fd, .events = POLLIN };
	while (1) {
		ret = poll(&fds, 1, 1000);
		if (ret < 0) {
			perror("poll");
			break;
		}

		if (fds.revents & POLLIN) {
			// Receive packets
			ret = recv(sock_fd, &desc, sizeof(desc), 0);
			if (ret < 0) {
				perror("recv");
				break;
			}

			printf("Received a packet of size %d\n", desc.len);
			// Process packet data here
		}
	}

	munmap(bufs, umem.len);
	free((void *)umem.addr);
	close(sock_fd);
	return 0;
}
