include podman.mk

subdir-y += capability
subdir-y += cmake
subdir-y += coreutils
subdir-y += code-formatter
subdir-y += criu
subdir-y += ffmpeg
subdir-y += fmtlib
subdir-y += fstabd
subdir-y += heatmap
subdir-y += io_uring
subdir-y += json-c
subdir-y += libguestfs
subdir-y += libosinfo
subdir-y += lsof
subdir-y += memcached
subdir-y += nasm
subdir-y += NetworkManager
subdir-y += ostree
subdir-y += perf
subdir-${HAVE_PODMAN} += podman
subdir-y += psmisc
subdir-y += readline
subdir-y += redis
subdir-y += util-linux
subdir-y += vim
subdir-y += zlib
