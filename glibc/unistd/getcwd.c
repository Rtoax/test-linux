#include <stdio.h>
#include <unistd.h>


int main(void)
{
    char buffer[1024];

    getcwd(buffer, sizeof(buffer));
    printf("PWD: %s\n", buffer);

    return 0;
}