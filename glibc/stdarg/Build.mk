include gcc.mk

target-y += delete_files
target-y += sum_int
target-y += __VA_ARGS__
target-y += va_arg
target-y += va_start
target-y += va_copy

target-cpp-${call gcc_ge,8,0,0} += __VA_OPT__

prog-y += ${target-y} ${target-cpp-y}
