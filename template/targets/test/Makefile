target-shell-y := env.sh
target-shell-y += env.sh.1
target-shell-y += env.sh.9
target-shell-y += env.sh.10

SHELL_ENVS_env.sh := -e TEST_LINUX_TEMPLATE_TARGETS_SHELL_ENV=rtoax
SHELL_ENVS_env.sh.1 := ${SHELL_ENVS_env.sh}
SHELL_ENVS_env.sh.9 := ${SHELL_ENVS_env.sh}
SHELL_ENVS_env.sh.10 := ${SHELL_ENVS_env.sh}

SHELL_ARGS_env.sh := abc
SHELL_ARGS_env.sh.1 := def
SHELL_ARGS_env.sh.9 := uvw
SHELL_ARGS_env.sh.10 := xyz

target-mk-y += test.mk test.mk.1 test.mk.9 test.mk.10
target-mk-y += test.mak test.mak.1 test.mak.9 test.mak.10
ARGS_test.mk := TEST_MK_DEF_1=0
ARGS_test.mk.1 := TEST_MK_DEF_1=1
ARGS_test.mk.9 := TEST_MK_DEF_1=9
ARGS_test.mk.10 := TEST_MK_DEF_1=10
ARGS_test.mak := TEST_MAK_DEF_1=0
ARGS_test.mak.1 := TEST_MAK_DEF_1=1
ARGS_test.mak.9 := TEST_MAK_DEF_1=9
ARGS_test.mak.10 := TEST_MAK_DEF_1=10

target-prog-y := test-args.sh
PROG_ARGS_test-args.sh := RRRRRRRRRRRRR TTTTTTTTTTT

include main.mk
