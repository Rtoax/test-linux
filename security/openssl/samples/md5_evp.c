#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include <openssl/evp.h>

/* Function: Calculate the MD5 hash of a file using OpenSSL's EVP API */
void calculate_md5(const char *filename, unsigned char *md5_result)
{
	FILE *file = fopen(filename, "rb");
	if (!file) {
		perror("Unable to open file");
		exit(EXIT_FAILURE);
	}

	/* Create a new EVP_MD_CTX */
	EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
	if (!md_ctx) {
		perror("Failed to create EVP_MD_CTX");
		fclose(file);
		exit(EXIT_FAILURE);
	}

	/* Get the MD5 digest method */
	const EVP_MD *md5 = EVP_md5();
	if (EVP_DigestInit_ex(md_ctx, md5, NULL) != 1) {
		perror("EVP_DigestInit_ex failed");
		EVP_MD_CTX_free(md_ctx);
		fclose(file);
		exit(EXIT_FAILURE);
	}

	unsigned char buffer[1024];
	size_t bytes_read;

	while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
		if (EVP_DigestUpdate(md_ctx, buffer, bytes_read) != 1) {
			perror("EVP_DigestUpdate failed");
			EVP_MD_CTX_free(md_ctx);
			fclose(file);
			exit(EXIT_FAILURE);
		}
	}

	if (ferror(file)) {
		perror("Error reading file");
		EVP_MD_CTX_free(md_ctx);
		fclose(file);
		exit(EXIT_FAILURE);
	}

	if (EVP_DigestFinal_ex(md_ctx, md5_result, NULL) != 1) {
		perror("EVP_DigestFinal_ex failed");
		EVP_MD_CTX_free(md_ctx);
		fclose(file);
		exit(EXIT_FAILURE);
	}

	EVP_MD_CTX_free(md_ctx);
	fclose(file);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
		return EXIT_FAILURE;
	}

	unsigned char md5_result[EVP_MAX_MD_SIZE];
	calculate_md5(argv[1], md5_result);

	printf("MD5 hash of file %s: ", argv[1]);
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
		printf("%02x", md5_result[i]);
	}
	printf("\n");

	return EXIT_SUCCESS;
}
