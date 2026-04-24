/* SPDX-License-Identifier: MIT */
/*
 * Very basic proof-of-concept for doing a copy with linked SQEs. Needs a
 * bit of error handling and short read love.
 */
#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "liburing.h"

#define QD    64         // io_uring queue length
#define BS    (32*1024)

struct io_data {
	size_t offset;
	int index;
	struct iovec iov;
};

static int infd, outfd;
static unsigned inflight;

// Create read->write SQE chain
static void queue_rw_pair(struct io_uring *ring, off_t size, off_t offset)
{
	struct io_uring_sqe *sqe;
	struct io_data *data;
	void *ptr;

	ptr = malloc(size + sizeof(*data));
	data = ptr + size;
	data->index = 0;
	data->offset = offset;
	data->iov.iov_base = ptr;
	data->iov.iov_len = size;

	// Get valide SQE
	sqe = io_uring_get_sqe(ring);
	// Prepare read request
	io_uring_prep_readv(sqe, infd, &data->iov, 1, offset);
	// Set LINK mode
	sqe->flags |= IOSQE_IO_LINK;
	// Set data
	io_uring_sqe_set_data(sqe, data);

	// Get another valide SQE
	sqe = io_uring_get_sqe(ring);
	// Prepare write request
	io_uring_prep_writev(sqe, outfd, &data->iov, 1, offset);
	// Set data
	io_uring_sqe_set_data(sqe, data);
}

// Handled completion event:
// 1. release SQE buffer
// 2. notifier kernel already consume CQE
static int handle_cqe(struct io_uring *ring, struct io_uring_cqe *cqe)
{
	// Get CQE
	struct io_data *data = io_uring_cqe_get_data(cqe);
	data->index++;
	int ret = -1;

	if (cqe->res < 0) {
		if (cqe->res == -ECANCELED) {
			queue_rw_pair(ring, BS, data->offset);
			inflight += 2;
		} else {
			printf("cqe error: %s\n", strerror(cqe->res));
			ret = 1;
		}
	}

	// read->write chain done, release buffer
	if (data->index == 2) {
		void *ptr = (void *) data - data->iov.iov_len;
		free(ptr);
	}

	// Notifier kernel already consume CQE event
	io_uring_cqe_seen(ring, cqe);
	return ret;
}

static int copy_file(struct io_uring *ring, off_t insize)
{
	struct io_uring_cqe *cqe;
	size_t this_size;
	off_t offset;

	offset = 0;
	// Handle data
	while (insize) {
		// number of SQE in running
		int has_inflight = inflight;
		// SQE threshold,
		// when number of SQE in running bigger than depth, block wait CQE done
		int depth;

		// data not done yet, io_uring queue not done neither
		while (insize && inflight < QD) {
			this_size = BS;
			// Last data size smaller than BS
			if (this_size > insize)
				this_size = insize;

			// Create read->write chain, use two SQE
			queue_rw_pair(ring, this_size, offset);
			offset += this_size;
			insize -= this_size;
			// Add 2 to running number of SQE
			inflight += 2;
		}

		// Have new SQE
		if (has_inflight != inflight)
			// commit to kernel
			io_uring_submit(ring);

		// If has data wait to handle
		if (insize)
			// Set threshold to queue length,
			// that is to say, when SQ queue done for use, CQE blocked wait.
			depth = QD;
		// All data handled commited
		else
			// Set threshold to 1
			// that is to say, if SQE not finished, block wait to CQE
			depth = 1;

		// All SQ queue run out, or all data(read->write request) commited
		while (inflight >= depth) {
			// wait kernel completion
			io_uring_wait_cqe(ring, &cqe);
			// handle completion event:
			// 1. release SQE buffer
			// 2. notifier kernel CQE consumed
			handle_cqe(ring, cqe);
			// number of SQE - 1
			inflight--;
		}
	}

	return 0;
}

static int setup_context(unsigned entries, struct io_uring *ring)
{
	io_uring_queue_init(entries, ring, 0);
	return 0;
}

static int get_file_size(int fd, off_t *size)
{
	struct stat st;

	if (fstat(fd, &st) < 0)
		return -1;
	if (S_ISREG(st.st_mode)) {
		*size = st.st_size;
		return 0;
	} else if (S_ISBLK(st.st_mode)) {
		unsigned long long bytes;

		if (ioctl(fd, BLKGETSIZE64, &bytes) != 0)
			return -1;

		*size = bytes;
		return 0;
	}

	return -1;
}

int main(int argc, char *argv[])
{
	struct io_uring ring;
	off_t insize;
	int ret;

	infd = open(argv[1], O_RDONLY);
	outfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (setup_context(QD, &ring))
		return 1;
	if (get_file_size(infd, &insize))
		return 1;

	ret = copy_file(&ring, insize);

	close(infd);
	close(outfd);
	io_uring_queue_exit(&ring);
	return ret;
}
