TARGETS := pam_authenticate

CC = clang
CFLAGS :=
LDFLAGS := -lpam -lpam_misc

pam_authenticate: pam_authenticate.o

all: ${TARGETS}

clean:
	rm -f ${TARGETS} *.o
