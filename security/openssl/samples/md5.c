#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

void calculate_md5(const char *filename, unsigned char *md5_result)
{
	FILE *file = fopen(filename, "rb");
	if (!file) {
		perror("无法打开文件");
		exit(EXIT_FAILURE);
	}

	MD5_CTX md5_context;
	MD5_Init(&md5_context);

	unsigned char buffer[1024];
	size_t bytes_read;

	while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
		MD5_Update(&md5_context, buffer, bytes_read);
	}

	MD5_Final(md5_result, &md5_context);

	fclose(file);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	unsigned char md5_result[MD5_DIGEST_LENGTH];
	calculate_md5(argv[1], md5_result);

	printf("File %s MD5 is: ", argv[1]);
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
		printf("%02x", md5_result[i]);
	}
	printf("\n");

	return EXIT_SUCCESS;
}
