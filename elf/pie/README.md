Position Independent Executables (PIE)
=========================================

Position Independent Executables (PIE) are an output of the hardened package
build process. A PIE binary and all of its dependencies are loaded into random
locations within virtual memory each time the application is executed.

After studying how file works from its source. We will conclude that:

```
if Elf32_Ehdr.e_type == ET_EXEC
	print executable
else if Elf32_Ehdr.e_type == ET_DYN
	if DT_FLAGS_1 dynamic section entry is present
		if DF_1_PIE is set in DT_FLAGS_1:
			print pie executable
		else
			print shared object
	else
		if file is executable by user, group or others
			print pie executable
		else
			print shared object
```

And here are some experiments that confirm that:

```
Executable generation        ELF type  DT_FLAGS_1  DF_1_PIE  chdmod +x      file 5.36
---------------------------  --------  ----------  --------  -------------- --------------
gcc -fpie -pie               ET_DYN    y           y         y              pie executable
gcc -fno-pie -no-pie         ET_EXEC   n           n         y              executable
gcc -shared                  ET_DYN    n           n         y              pie executable
gcc -shared                  ET_DYN    n           n         n              shared object
ld                           ET_EXEC   n           n         y              executable
ld -pie --dynamic-linker     ET_DYN    y           y         y              pie executable
ld -pie --no-dynamic-linker  ET_DYN    y           y         y              pie executable
```


# Links

* [Position Independent Executables (PIE)](https://www.redhat.com/en/blog/position-independent-executables-pie)
* StackOverflow: [Why does GCC create a shared object instead of an executable binary according to file?](https://stackoverflow.com/questions/34519521/why-does-gcc-create-a-shared-object-instead-of-an-executable-binary-according-to/55704865)

