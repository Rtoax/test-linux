SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


all:
	${Q}make -C posix
	${Q}make -C sysv
clean:
	${Q}make -C posix clean
	${Q}make -C sysv clean
