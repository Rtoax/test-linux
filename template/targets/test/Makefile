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

target-mk-y := test.mk
target-mk-y += test.mk.1
target-mk-y += test.mk.9
target-mk-y += test.mk.10

ARGS_test.mk := TEST_MK_DEF_1=0
ARGS_test.mk.1 := TEST_MK_DEF_1=1
ARGS_test.mk.9 := TEST_MK_DEF_1=9
ARGS_test.mk.10 := TEST_MK_DEF_1=10

include main.mk
