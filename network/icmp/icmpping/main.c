#include <stdio.h>
#include "icmpping.h"


int main(int argc, char * argv[])
{

    if (argc < 2)
    {
        printf("Usage: %s hostname/IP address\n\r", argv[0]);
        return (-1);
    }
    long int latency;


    int rslt = icmp_ping(argv[1], 1, 3, NULL, &latency);
    if(rslt == ICMPPING_SUCC)
        printf("ping \033[1;32m%s\033[m is OK. latency = %ld microseconds\n", argv[1], latency);
    else
        printf("ping \033[1;31m%s\033[m is not OK.\n", argv[1]);

    
    return 0;
}


