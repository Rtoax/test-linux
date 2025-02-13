SHELL = bash
include ../../../../tlbuild.mk


SRCS            =       memcpy.S         \
                        memset.S         \
                        memmove.S        \
                        rindex.S         \
                        strcasecmp.S     \
                        strchr.S         \
                        strcmp.S         \
                        strlen.S         \
                        strncmp.S        \
                        strcspn.S        \
                        strpbrk.S        \
                        strstr.S	 \
			read.S		 \
			write.S
OBJS	= $(SRCS:.S=.o)

LD	= ld
LDFLAGS	= -shared
ASM	= nasm
ASFLAGS	= -f elf64
RM	= rm -f
NAME	= libasm.so
TEST	= test

all: $(NAME) $(TEST)

%.o:	%.S
	$(ASM) $(ASFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(NAME)

$(TEST):
	${Q}make -C tests
	cp tests/tests $(TEST)

clean:
	$(RM) $(OBJS) $(NAME) $(TEST)
	${Q}make -C tests clean

re: all

.PHONY: all clean re
