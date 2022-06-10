#include <stdio.h>

#include "bitmask.h"

#define print_info(fmt...) fprintf(stderr, fmt)

int memshow(const void*in, int len)
{
    if(!in)
        return -1;
    char const *c = in;
    int i;
    for(i=0;i<len;i++, c++)
        printf("%02x ", (unsigned char)*c);
    printf("\n");
    return len;
}


static void demo_bitmask_test1()
{
    unsigned int nbits = 256;
    
    struct bitmask *mask1 = bitmask_alloc(nbits);

    memshow(mask1->maskp, nbits/8);

    bitmask_setbit(mask1, 2);
    memshow(mask1->maskp, nbits/8);
    
    bitmask_setall(mask1);
    memshow(mask1->maskp, nbits/8);

    bitmask_clearall(mask1);
    memshow(mask1->maskp, nbits/8);
    if(bitmask_isallclear(mask1)) {
        print_info("all clear.\n");
    }

    bitmask_setbit(mask1, 2);
    if(bitmask_isbitset(mask1, 2)) {
        print_info(" bit set.\n");
    }
    if(bitmask_isbitset(mask1, 3)) {
        print_info(" bit set.\n");
    }

    bitmask_parselist("0-255:3", mask1);

    char buf[1024] = {0};
    bitmask_displaylist(buf, 1024, mask1);
    print_info("%s\n", buf);
    
    bitmask_free(mask1);
}


int main()
{
    demo_bitmask_test1();
    

    return 0;
}


