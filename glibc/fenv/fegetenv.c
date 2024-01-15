#include <stdio.h>
#include <math.h>
#include <fenv.h>

#define _print(val) printf("%s:%x\n", #val, val)

int main(void)
{
    fenv_t envp;

    fegetenv(&envp);

    _print(envp);

    return 0;
}

