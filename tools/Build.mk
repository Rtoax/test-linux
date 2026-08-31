include git.mk
include libsmbios.mk
include mbw.mk
include ndctl.mk
include podman.mk
include tmux.mk
include zstd.mk

subdir-y += bc
subdir-y += binfmt
subdir-y += capability
subdir-y += capstone
subdir-y += cdrkit
subdir-y += cmake
subdir-y += coreutils
subdir-y += code-formatter
subdir-y += cpio
subdir-y += crash
subdir-y += criu
subdir-y += design-patterns
subdir-y += dialog
subdir-y += elfutils
subdir-y += ethtool
subdir-y += evtest
subdir-y += expect
subdir-y += ffmpeg
subdir-y += fmtlib
subdir-y += fontconfig
subdir-y += fstabd
subdir-y += gawk
subdir-y += gdisk
subdir-${HAVE_GIT} += git
subdir-y += grep
subdir-y += heatmap
subdir-y += hwloc
subdir-y += io_uring
subdir-y += iproute
subdir-y += jq
subdir-y += json-c
subdir-y += kasan
subdir-y += kbd
subdir-y += libblockdev
subdir-y += libisoburn
subdir-y += libnbd
subdir-${HAVE_LIBSMBIOS} += libsmbios
subdir-y += libguestfs
subdir-y += libosinfo
subdir-y += libtracefs
subdir-y += livepatch
subdir-y += lm_sensors
subdir-y += lsof
subdir-y += makeself
subdir-${HAVE_MBW} += mbw
subdir-y += memcached
subdir-y += nasm
subdir-y += nbd
subdir-y += net-tools
subdir-y += NetworkManager
subdir-y += ncurses
subdir-y += notcurses
subdir-y += nginx
subdir-y += ostree
subdir-y += pahole
subdir-y += perf
subdir-${HAVE_PODMAN} += podman
subdir-y += printk
subdir-y += procps-ng
subdir-y += psmisc
subdir-y += readline
subdir-y += redis
subdir-y += sed
subdir-y += skopeo
subdir-y += static_key
subdir-y += sudo
subdir-${HAVE_SYSBENCH} += sysbench
subdir-y += sysstat
subdir-y += tcpdump
subdir-${HAVE_TMUX} += tmux
subdir-y += util-linux
subdir-y += vim
subdir-y += xterm
subdir-y += zlib
subdir-${HAVE_NDCTL} += ndctl
subdir-${HAVE_ZSTD} += zstd
