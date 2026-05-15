/**
 * Test __attribute__ packed and aligned
 *
 * - requested alignment number is a positive power of 2
 * - or use -fpack-struct=1
 */
#include <stdio.h>

#define CHK(st, sz) _Static_assert(sizeof(struct st) == sz, #st)
#define PNT(st) printf("size of struct %-8s is %ld\n", #st, sizeof(struct st))

/**
 * support by GCC, MSVC, Clang, ARMCC, IAR 
 */
#pragma pack(push, 1)
struct s0 {
	int i1;
	char c;
	int i2;
};
#pragma pack(pop)
CHK(s0, 9);

#pragma pack(1)
struct s1 {
	int i1;
	char c;
	int i2;
};
#pragma pack()
CHK(s1, 9);

struct __attribute__((packed)) s2 {
	int i1;
	char c;
	int i2;
};
CHK(s2, 9);

/**
 * attribute before 'struct' is not useful, and GCC do not complain, CLANG does.
 */
#if !defined(__clang__)
__attribute__((packed, aligned(1))) struct s2_1 {
	int i1;
	char c;
	int i2;
};
CHK(s2_1, 12);
#endif

struct s3 {
	int i1;
	char c;
	int i2;
} __attribute__((packed));
CHK(s3, 9);

struct s4 {
	int i1;
	char c;
	int i2;
} __attribute__((packed, aligned(1)));
CHK(s4, 9);

struct s4_1 {
	int i1;
	char c;
	int i2;
} __attribute__((packed, aligned(2)));
CHK(s4_1, 10);

struct s4_2 {
	int i1;
	char c;
	int i2;
} __attribute__((packed, aligned(4)));
CHK(s4_2, 12);

struct s5 {
	int i1;
	char c;
	int i2;
} __attribute__((aligned(1)));
CHK(s5, 12);

struct s5_1 {
	int i1;
	char c;
	int i2;
} __attribute__((aligned(4)));
CHK(s5_1, 12);

struct s6 {
	int i1;
	char c;
	int i2;
} __attribute__((packed)) __attribute__((aligned(1)));
CHK(s6, 9);

struct s {
	int i1;
	char c;
	int i2;
};
CHK(s, 12);

int main(void)
{
	PNT(s);
	PNT(s1);
	PNT(s2);
	PNT(s3);
	PNT(s4);
	PNT(s4_1);
	PNT(s4_2);
	PNT(s5);
	PNT(s5_1);
	PNT(s6);
	return 0;
}
