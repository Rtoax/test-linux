Arch
====

# ASM

## Inline Assembly in Linux C

### AT&T Synx

`OP-code src dst`, for example: `"movl $78, %1 \n"`.


### asm()

```
asm (
	assembler template
	: output operands (optional)
	: input operands (optional)
	: list of clobbered registers (optional)
);
```


# Cross Compile

```
$ aarch64-linux-gnu-gcc -print-sysroot
/usr/aarch64-linux-gnu/sys-root
```

