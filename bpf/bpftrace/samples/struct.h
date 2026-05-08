#pragma once
#define PACKED __attribute__((packed))

struct s1 {
} PACKED;

struct s3 {
	int i;
	char c;
} __attribute__((packed));
