SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


##
## EPITECH PROJECT, 2018
## File description:
## Makefile
##

NAME	=	tests

SRC	:=	tests.c
SRC	+=	test_memcpy.c		\
		test_memmove.c		\
		test_memset.c		\
		test_rindex.c		\
		test_strcasecmp.c	\
		test_strchr.c		\
		test_strcmp.c		\
		test_strcspn.c		\
		test_strlen.c		\
		test_strncmp.c		\
		test_strstr.c		\
		test_strpbrk.c

OBJ	=	$(SRC:.c=.o)
GCDA	=	$(SRC:.c=.gcda)
GCDO	=	$(SRC:.c=.gcno)
LDFLAGS	+=	-ldl  --coverage
CFLAGS	+=	-fprofile-arcs -ftest-coverage
CFLAGS	+=	-O0 -ggdb -g

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(GCDA) $(GCDO) $(NAME)

re: all

.PHONY: all clean re
