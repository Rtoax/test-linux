TARGETS :=
TARGETS += ceil
TARGETS += copysign
TARGETS += exp
TARGETS += sqrt

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -lm
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
ceil: ceil.o
exp: exp.o
sqrt: sqrt.o
copysign: copysign.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.log
	@rm -rf tmpd-* tmp-*
