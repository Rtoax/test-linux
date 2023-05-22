Gcov
====

- 2019-06-14 Rong Tao Create This

```
$ gcc -fprofile-arcs -ftest-coverage tmp.c
$ a.out
$ gcov tmp.c
90.00% of 10 source lines executed in file tmp.c
Creating tmp.c.gcov.
The fle ‘tmp.c.gcov’ contains output from gcov. Here is a sample:
-: 0:Source:tmp.c
-: 0:Graph:tmp.gcno
-: 0:Data:tmp.gcda
-: 0:Runs:1
-: 0:Programs:1
-: 1:#include <stdio.h>
-: 2:
-: 3:int main (void)
	1: 4:{
1: 5: int i, total;
   -: 6:
	   1: 7: total = 0;
   -: 8:
	   11: 9: for (i = 0; i < 10; i++)
	   10: 10: total += i;
   -: 11:
	   1: 12: if (total != 45)
#####: 13: printf ("Failure\n");
	   -: 14: else
	   1: 15: printf ("Success\n");
1: 16: return 0;
   -: 17:}
```

When you use the ‘-a’ option, you will get individual block counts, and the output looks like this:

```
-: 0:Source:tmp.c
-: 0:Graph:tmp.gcno
-: 0:Data:tmp.gcda
-: 0:Runs:1
-: 0:Programs:1
-: 1:#include <stdio.h>
-: 2:
-: 3:int main (void)
	1: 4:{
1: 4-block 0
	   1: 5: int i, total;
   -: 6:
	   1: 7: total = 0;
   -: 8:
	   11: 9: for (i = 0; i < 10; i++)
	   11: 9-block 0
	   10: 10: total += i;
10: 10-block 0
		-: 11:
		1: 12: if (total != 45)
		1: 12-block 0
#####: 13: printf ("Failure\n");
		$$$$$: 13-block 0
		-: 14: else
		1: 15: printf ("Success\n");
1: 15-block 0
	   1: 16: return 0;
1: 16-block 0
	   -: 17:}
```


# 汇编分析

```c
int addi(int v, int i)
{
	return v + i;
}
```

## 原始

```asm
addi:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	ret
```

## -fprofile-arcs

```asm
addi:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movq	__gcov0.addi(%rip), %rax
	addq	$1, %rax
	movq	%rax, __gcov0.addi(%rip)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	ret
```

## -fprofile-arcs -ftest-converge

```asm
addi:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movq	__gcov0.addi(%rip), %rax
	addq	$1, %rax
	movq	%rax, __gcov0.addi(%rip)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	ret
```

## -fprofile-generate

> man gcc:
> The following options are enabled: -fprofile-arcs, -fprofile-values, -finline-functions, and -fipa-bit-cp

```
addi:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movq	__gcov_indirect_call@gottpoff(%rip), %rax
	movq	%fs:(%rax), %rax
	testq	%rax, %rax
	je	.L2
	movl	$addi, %esi
	movl	$2017797125, %edi
	call	__gcov_indirect_call_profiler_v4
.L2:
	movq	__gcov0.addi(%rip), %rax
	addq	$1, %rax
	movq	%rax, __gcov0.addi(%rip)
	movq	__gcov7.addi(%rip), %rax
	testq	%rax, %rax
	jne	.L3
	movq	__gcov_time_profiler_counter(%rip), %rax
	addq	$1, %rax
	movq	%rax, __gcov7.addi(%rip)
	movq	%rax, __gcov_time_profiler_counter(%rip)
.L3:
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	leave
	ret
```

