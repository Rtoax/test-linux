include git.mk
include libsmbios.mk
include podman.mk
include zstd.mk

subdir-y += binfmt
subdir-y += capability
subdir-y += cmake
subdir-y += coreutils
subdir-y += code-formatter
subdir-y += criu
subdir-y += ffmpeg
subdir-y += fmtlib
subdir-y += fstabd
subdir-y += gdisk
subdir-${HAVE_GIT} += git
subdir-y += heatmap
subdir-y += io_uring
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
subdir-y += nginx
subdir-y += ostree
subdir-y += perf
subdir-${HAVE_PODMAN} += podman
subdir-y += psmisc
subdir-y += readline
subdir-y += redis
subdir-y += static_key
subdir-y += util-linux
subdir-y += vim
subdir-y += zlib
subdir-${HAVE_ZSTD} += zstd
