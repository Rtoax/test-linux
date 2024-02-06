#include <stdio.h>
#include <malloc.h>
#include <unwind.h>
#include <execinfo.h>


struct trace_arg
{
	void **array;
	_Unwind_Word cfa;
	int cnt;
	int size;
};

static inline void *unwind_arch_adjustment(void *prev, void *addr)
{
	return addr;
}

static _Unwind_Reason_Code backtrace_helper(struct _Unwind_Context *ctx, void *a)
{
	struct trace_arg *arg = a;

	/* We are first called with address in the __backtrace function.
	Skip it.  */
	if (arg->cnt != -1) {
		arg->array[arg->cnt] =(void *) _Unwind_GetIP(ctx);
		if (arg->cnt > 0)
			arg->array[arg->cnt] = unwind_arch_adjustment(
				arg->array[arg->cnt - 1], arg->array[arg->cnt]);

		/* Check whether we make any progress.  */
		_Unwind_Word cfa = _Unwind_GetCFA(ctx);

		if (arg->cnt > 0 &&
		    arg->array[arg->cnt - 1] == arg->array[arg->cnt] &&
		    cfa == arg->cfa)
			return _URC_END_OF_STACK;

		arg->cfa = cfa;
	}
	if (++arg->cnt == arg->size)
		return _URC_END_OF_STACK;
	return _URC_NO_REASON;
}

int __backtrace(void **array, int size)
{
	struct trace_arg arg = {
		.array = array,
		.cfa = 0,
		.size = size,
		.cnt = -1,
	};

	if (size <= 0)
		return 0;

	_Unwind_Backtrace(backtrace_helper, &arg);

	/* _Unwind_Backtrace seems to put NULL address above
	 * _start.  Fix it up here.  */
	if (arg.cnt > 1 && arg.array[arg.cnt - 1] == NULL)
		--arg.cnt;

	return arg.cnt != -1 ? arg.cnt : 0;
}


/* Obtain a backtrace and print it to stdout. */
void print_trace(void)
{
	void *array[10240];
	size_t size;
	char **strings;
	size_t i;
	size = __backtrace(array, 10240);
	strings = backtrace_symbols(array, size);

	FILE *fp = fopen("backtrace.txt", "w");
	backtrace_symbols_fd(array, size, fileno(fp));
	fclose(fp);

	printf("Obtained %zd stack frames.\n", size);
	for (i = 0; i < size; i++)
		printf(">> %s\n", strings[i]);

	free(strings);
}

void dummy_function(void)
{
	print_trace();
}

int main(void)
{
	dummy_function();
	return 0;
}
