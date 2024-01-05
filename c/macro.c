#include <stdio.h>

struct attr {
	void (*show)(void);
};

#define __ATTR_RO(_name) {		\
	.show = _name##_show		\
}

#define ATTR_RO(_name)	\
	struct attr attr_##_name = __ATTR_RO(_name)

void print_show(void) { }

ATTR_RO(print);

int main(void)
{
	return 0;
}
