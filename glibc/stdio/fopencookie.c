#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define INIT_BUF_SIZE 4

struct memfile_cookie {
	char   *buf;		/* Dynamically sized buffer for data */
	size_t  allocated;	/* Size of buf */
	size_t  endpos;		/* Number of characters in buf */
	off_t   offset;		/* Current file offset in buf */
};

ssize_t memfile_write(void *c, const char *buf, size_t size)
{
	char *new_buff;
	struct memfile_cookie *cookie = c;

	/* Buffer too small? Keep doubling size until big enough. */

	while (size + cookie->offset > cookie->allocated) {
		new_buff = realloc(cookie->buf, cookie->allocated * 2);
		if (new_buff == NULL)
			return -1;
		cookie->allocated *= 2;
		cookie->buf = new_buff;
	}

	memcpy(cookie->buf + cookie->offset, buf, size);

	cookie->offset += size;
	if (cookie->offset > cookie->endpos)
		cookie->endpos = cookie->offset;

	return size;
}

ssize_t memfile_read(void *c, char *buf, size_t size)
{
	ssize_t xbytes;
	struct memfile_cookie *cookie = c;

	/* Fetch minimum of bytes requested and bytes available. */

	xbytes = size;
	if (cookie->offset + size > cookie->endpos)
		xbytes = cookie->endpos - cookie->offset;
	if (xbytes < 0)	 /* offset may be past endpos */
		xbytes = 0;

	memcpy(buf, cookie->buf + cookie->offset, xbytes);

	cookie->offset += xbytes;
	return xbytes;
}

int memfile_seek(void *c, off_t *offset, int whence)
{
	off_t new_offset;
	struct memfile_cookie *cookie = c;

	if (whence == SEEK_SET)
		new_offset = *offset;
	else if (whence == SEEK_END)
		new_offset = cookie->endpos + *offset;
	else if (whence == SEEK_CUR)
		new_offset = cookie->offset + *offset;
	else
		return -1;

	if (new_offset < 0)
		return -1;

	cookie->offset = new_offset;
	*offset = new_offset;
	return 0;
}

int memfile_close(void *c)
{
	struct memfile_cookie *cookie = c;

	free(cookie->buf);
	cookie->allocated = 0;
	cookie->buf = NULL;

	return 0;
}

int main(int argc, char *argv[])
{
	cookie_io_functions_t  memfile_func = {
		.read  = memfile_read,
		.write = memfile_write,
		.seek  = (void *)memfile_seek,
		.close = memfile_close
	};
	FILE *stream;
	struct memfile_cookie mycookie;
	size_t nread;
	char buf[1000];

	/* Set up the cookie before calling fopencookie(). */

	mycookie.buf = malloc(INIT_BUF_SIZE);
	if (mycookie.buf == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	mycookie.allocated = INIT_BUF_SIZE;
	mycookie.offset = 0;
	mycookie.endpos = 0;

	stream = fopencookie(&mycookie, "w+", memfile_func);
	if (stream == NULL) {
		perror("fopencookie");
		exit(EXIT_FAILURE);
	}

	/* Write command-line arguments to our file. */

	for (size_t j = 1; j < argc; j++)
		if (fputs(argv[j], stream) == EOF) {
			perror("fputs");
			exit(EXIT_FAILURE);
		}

	/* Read two bytes out of every five, until EOF. */

	for (long p = 0; ; p += 5) {
		if (fseek(stream, p, SEEK_SET) == -1) {
			perror("fseek");
			exit(EXIT_FAILURE);
		}
		nread = fread(buf, 1, 2, stream);
		if (nread == 0) {
			if (ferror(stream) != 0) {
				fprintf(stderr, "fread failed\n");
				exit(EXIT_FAILURE);
			}
			printf("Reached end of file\n");
			break;
		}

		printf("/%.*s/\n", (int) nread, buf);
	}

	free(mycookie.buf);

	exit(EXIT_SUCCESS);
}
