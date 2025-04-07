#!/bin/env python

file = "generated_functions.h"
num = 80000

# generate_code.py
with open(file, "w") as f:
    for i in range(num):
        f.write(f"static int __attribute__((optimize(\"-O0\"))) func_{i}(void) {{ \n\
            char volatile buff[1024] = {{\"Hello World from {i}\" \n\
                \"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\" \n\
                \"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\" \n\
                \"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\" \n\
                \"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\" \n\
                \"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\" \n\
                \"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\" \n\
                \"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\" \n\
            }}; \n\
            printk(\"function %s\", \"func_{i}\"); \n\
            printk(\"buff %s\", buff); \n\
            return {i}; \n\
        }}\n"
        )
    f.write(f"static unsigned long __attribute__((optimize(\"-O0\"))) \n\
        call_big_text2(void) {{ \n\
        unsigned long volatile count = 0; \n\
        return 0; \n\
    ")
    for i in range(num):
        f.write(f"count += func_{i}(); \n")
    f.write(f"return count; \n")
    f.write(f"}} \n")
