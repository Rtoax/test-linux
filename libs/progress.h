// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#ifndef __PROGRESS_H
#define __PROGRESS_H
#include <stdio.h>

typedef struct {
	char chr;	/*tip char*/
	char *title;	/*tip string*/
	int style;	/*progress style*/
	int max;	/*maximum value*/
	float offset;
	char *pro;
} progress_t;

#define PROGRESS_NUM_STYLE 0
#define PROGRESS_CHR_STYLE 1
#define PROGRESS_BGC_STYLE 2

extern void progress_init(progress_t *, char *, int, int);

extern void progress_show(progress_t *, float);
extern void progress_reset(progress_t *, char *);

extern void progress_destroy(progress_t *);

#endif
