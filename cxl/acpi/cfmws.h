/**
 * CXL Fixed Memory Window Structure (CFMWS)
 * Since CXL 3.0
 */
#include <stdint.h>

struct cfmws {
	uint8_t type;
	uint8_t reserved;
	uint16_t record_length;
	uint32_t reserved2;
	uint8_t base_hpa;
	uint8_t window_size;
	/**
	 * Encoded Number of Interleave Ways (ENIW)
	 */
	uint8_t eniw;
	uint8_t interleave_arithmetic;
	uint8_t reserved3[2];
	/**
	 * Host Bridge Interleave Granularity (HBIG)
	 */
	uint32_t hbig;
	uint16_t window_restrictions;
	/* QTAG ID */
	uint16_t qtag_id;
	uint32_t interleave_target_list[];
};

struct cfmws *read_and_alloc_cfmws(FILE *fp);
void display_cfmws(struct cfmws *cfmws);
