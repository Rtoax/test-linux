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

all: $(NAME)

%.o:	%.S
	$(ASM) $(ASFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS) $(NAME)

re: all

.PHONY: all clean re
