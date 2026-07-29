include git.mk
include libsmbios.mk
include ndctl.mk
include podman.mk
include tmux.mk
include zstd.mk

subdir-y += binfmt
subdir-y += capability
subdir-y += capstone
subdir-y += cmake
subdir-y += coreutils
subdir-y += code-formatter
subdir-y += crash
subdir-y += criu
subdir-y += evtest
subdir-y += expect
subdir-y += ffmpeg
subdir-y += fmtlib
subdir-y += fstabd
subdir-y += gdisk
subdir-${HAVE_GIT} += git
subdir-y += heatmap
subdir-y += io_uring
subdir-y += iproute
subdir-y += jq
subdir-y += json-c
subdir-y += kasan
subdir-${HAVE_LIBSMBIOS} += libsmbios
subdir-y += libguestfs
subdir-y += libosinfo
subdir-y += livepatch
subdir-y += lsof
subdir-y += memcached
subdir-y += nasm
subdir-y += NetworkManager
subdir-y += ncurses
subdir-y += notcurses
subdir-y += nginx
subdir-y += ostree
subdir-y += pahole
subdir-y += perf
subdir-${HAVE_PODMAN} += podman
subdir-y += psmisc
subdir-y += readline
subdir-y += redis
subdir-y += static_key
subdir-y += sysstat
subdir-${HAVE_TMUX} += tmux
subdir-y += util-linux
subdir-y += vim
subdir-y += xterm
subdir-y += zlib
subdir-${HAVE_NDCTL} += ndctl
subdir-${HAVE_ZSTD} += zstd
