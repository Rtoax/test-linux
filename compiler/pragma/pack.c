/**
 * or use -fpack-struct=1
 */
#include <stdio.h>

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

#pragma pack(1)
struct s1 {
	int i1;
	char c;
	int i2;
};
#pragma pack()

struct __attribute__((packed)) s2 {
	int i1;
	char c;
	int i2;
};

struct s3 {
	int i1;
	char c;
	int i2;
} __attribute__((packed));

struct s4 {
	int i1;
	char c;
	int i2;
} __attribute__((packed, aligned(1)));

struct s5 {
	int i1;
	char c;
	int i2;
} __attribute__((aligned(1)));

struct s {
	int i1;
	char c;
	int i2;
};

int main(void)
{
	printf("size of struct s %ld\n", sizeof(struct s));
	printf("size of struct s0 %ld\n", sizeof(struct s0));
	printf("size of struct s1 %ld\n", sizeof(struct s1));
	printf("size of struct s2 %ld\n", sizeof(struct s2));
	printf("size of struct s3 %ld\n", sizeof(struct s3));
	printf("size of struct s4 %ld\n", sizeof(struct s4));
	printf("size of struct s5 %ld\n", sizeof(struct s5));
	return 0;
}
