#ifndef __jemalloc_counter_h
#define __jemalloc_counter_h

#include <string.h>

#define NR_COUNTER  7

static const char *counter_string[] = {
	"num_ops",
	"num_wait",
	"num_spin_acq",
	"num_owner_switch",
	"total_wait_time",
	"max_wait_time",
	"max_num_thds",
//	num_ops		   0
//	num_wait		  1
//	num_spin_acq	  2
//	num_owner_switch  3
//	total_wait_time   4
//	max_wait_time	 5
//	max_num_thds	  6
};


#define CNT_STRING(basic, cnt_name) ({\
	char str[256] = {0};\
	sprintf(str, "%s", basic);\
	strcat(str, cnt_name);\
	str;\
})


#endif /*<__jemalloc_counter_h>*/
