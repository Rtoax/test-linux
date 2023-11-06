TARGETS += __attribute__alias
TARGETS += __attribute__cleanup
TARGETS += __attribute__const
TARGETS += __attribute__constructor
TARGETS += __attribute__deprecated
TARGETS += __attribute__error
TARGETS += __attribute__format
TARGETS += __attribute____gnu_inline__
TARGETS += __attribute____naked__
TARGETS += __attribute__nocf_check
TARGETS += __attribute__nonnull
TARGETS += __attribute__noreturn
TARGETS += __attribute__optimize_omit-frame-pointer
TARGETS += __attribute____pure__
TARGETS += __attribute__randomize_layout
TARGETS += __attribute__section-initcall
TARGETS += __attribute__section-readmostly
TARGETS += __attribute__vector_size
TARGETS += __attribute__weak

all: ${TARGETS}

__attribute__alias: __attribute__alias.o
__attribute__cleanup: __attribute__cleanup.o
__attribute__const: __attribute__const.o
__attribute__constructor: __attribute__constructor.o
__attribute__deprecated: __attribute__deprecated.o
__attribute__error: __attribute__error.o
__attribute__format: __attribute__format.o
__attribute____gnu_inline__: __attribute____gnu_inline__.o
__attribute____naked__: __attribute____naked__.o
__attribute__nocf_check: __attribute__nocf_check.o
__attribute__nonnull: __attribute__nonnull.o
__attribute__noreturn: __attribute__noreturn.o
__attribute__optimize_omit-frame-pointer: __attribute__optimize_omit-frame-pointer.o
__attribute____pure__: __attribute____pure__.o
__attribute__randomize_layout: __attribute__randomize_layout.o
__attribute__section-initcall: __attribute__section-initcall.o
__attribute__section-readmostly: __attribute__section-readmostly.o
__attribute__vector_size: __attribute__vector_size.o
__attribute__weak: __attribute__weak.o

ifneq ($(shell uname -m),aarch64)
CFLAGS___attribute__nocf_check := -fcf-protection
else
$(warning TODO: Does aarch64 support -fcf-protection=full)
endif

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))



clean:
	rm -f ${TARGETS} *.o
