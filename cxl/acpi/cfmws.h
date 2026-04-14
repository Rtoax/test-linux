/**
 * CXL Fixed Memory Window Structure (CFMWS)
 * CXL 3.0 Specification, Section 9.17.1.3
 */
#pragma once
#include <stdint.h>

struct cfmws {
	uint8_t type;
	uint8_t reserved;
	/**
	 * ::record_length = 0x24 + 4 * NIW
	 */
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
	 *
	 * The number of consecutive bytes within the interleave that are
	 * decoded by each target in the Interleave Target List represented in
	 * an encoded format.
	 */
	uint32_t hbig;
	uint16_t window_restrictions;
	/* QTAG ID */
	uint16_t qtag_id;
	/**
	 * Number of Interleave Ways (NIW)
	 */
	uint32_t interleave_target_list[];
};

void display_cfmws(struct cfmws *cfmws);
