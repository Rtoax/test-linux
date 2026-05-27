# SPDX-License-Identifier: GPL-3.0
subdir-y += alias
subdir-y += array
subdir-y += bash-completion
subdir-y += commands
subdir-y += env-passing
subdir-y += math
subdir-y += network
subdir-y += string

shell-y += args.sh
shell-y += call.sh
shell-y += c_code.sh
shell-y += cmdline.sh
shell-y += digit.sh
shell-y += function.sh
shell-y += nested-func.sh
shell-y += num.sh
shell-y += open-fd.sh
shell-y += parallel.sh
shell-y += pipe.sh
shell-y += replace.sh
shell-y += ret.sh
shell-y += root-chk.sh
shell-y += select.sh
shell-y += shebang.sh
shell-y += stat.sh
shell-y += sudo.sh
shell-y += tracing.sh
shell-y += trap.sh
shell-y += while.sh
shell-y += SUDO_USER.sh
shell-y += BASH_SOURCE.sh

SHELL_ARGS_stat.sh := /etc/os-release /etc/hosts
