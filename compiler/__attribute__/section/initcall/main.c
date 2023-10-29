#include <stdio.h>
#include "log.h"
#include "init.h"


int _initdata boot = 0;

int init_main1()
{
	log("rongtao1\n");
}
int init_main2()
{
	log("rongtao2\n");
}

INIT(init_main1);
INIT(init_main2);

int main(void)
{
	printf("boot = %d\n", 0);
	do_initcalls();
}