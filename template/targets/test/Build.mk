shell-y := test-env.sh
shell-y += test-env.sh.1
shell-y += test-env.sh.9
shell-y += test-env.sh.10

SHELL_ENVS_test-env.sh := -e TEST_LINUX_TEMPLATE_TARGETS_SHELL_ENV=rtoax
SHELL_ENVS_test-env.sh.1 := ${SHELL_ENVS_test-env.sh}
SHELL_ENVS_test-env.sh.9 := ${SHELL_ENVS_test-env.sh}
SHELL_ENVS_test-env.sh.10 := ${SHELL_ENVS_test-env.sh}

SHELL_ARGS_test-env.sh := abc
SHELL_ARGS_test-env.sh.1 := def
SHELL_ARGS_test-env.sh.9 := uvw
SHELL_ARGS_test-env.sh.10 := xyz

make-y += test.mk test.mk.1 test.mk.9 test.mk.10
make-y += test.mak test.mak.1 test.mak.9 test.mak.10
ARGS_test.mk := TEST_MK_DEF_1=0
ARGS_test.mk.1 := TEST_MK_DEF_1=1
ARGS_test.mk.9 := TEST_MK_DEF_1=9
ARGS_test.mk.10 := TEST_MK_DEF_1=10
ARGS_test.mak := TEST_MAK_DEF_1=0
ARGS_test.mak.1 := TEST_MAK_DEF_1=1
ARGS_test.mak.9 := TEST_MAK_DEF_1=9
ARGS_test.mak.10 := TEST_MAK_DEF_1=10

prog-y += test-env.sh
prog-y += test-env.sh.1
prog-y += test-env.sh.2
prog-y += test-args.sh

PROG_ENVS := -e PROG_ENVS=1
PROG_ENVS_test-env.sh := -e TEST_LINUX_TEMPLATE_TARGETS_SHELL_ENV=rtoax
PROG_ENVS_test-env.sh.1 := ${PROG_ENVS_test-env.sh}
PROG_ENVS_test-env.sh.2 := ${PROG_ENVS_test-env.sh}

PROG_ARGS := PROG_ARGS
PROG_ARGS_test-args.sh := RRRRRRRRRRRRR TTTTTTTTTTT

target-y += main
target-y += gcc
target-y += clang clang.1

target-liba-y += libfoobar.a
target-libso-y += libfoobar.so

main-objs := foo.o bar.o
main-deps := foo.h bar.h
foo.o-deps := foo.h
bar.o-deps := bar.h
main.o-deps := foo.h bar.h
libfoobar.a-objs += foo.a.o bar.a.o
libfoobar.so-objs += foo.so.o bar.so.o
foo.a.o-deps := foo.h
bar.a.o-deps := bar.h
foo.so.o-deps := foo.h
bar.so.o-deps := bar.h

clang.1-objs := clang.1.o

CC_clang := clang

target-cpp-y += cpp

target-liba-y += libfoobar++.a
target-libso-cpp-y += libfoobar++.so

cpp-objs += foo.cpp.o
cpp-objs += bar.cpp.o
foo.cpp.o-deps := foo.hpp
bar.cpp.o-deps := bar.hpp
cpp.cpp.o-deps := foo.hpp bar.hpp

libfoobar++.a-objs += foo.cpp.a.o bar.cpp.a.o
libfoobar++.so-objs += foo.cpp.so.o bar.cpp.so.o
foo.cpp.a.o-deps := foo.hpp
bar.cpp.a.o-deps := bar.hpp
foo.cpp.so.o-deps := foo.hpp
bar.cpp.so.o-deps := bar.hpp
