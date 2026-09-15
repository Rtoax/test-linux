include anaconda.mk
include flatpak.mk
include os.mk

subdir-y += alpine
subdir-${HAVE_ANACONDA} += anaconda
subdir-y += apt
subdir-y += dpkg
subdir-${HAVE_FLATPAK} += flatpak
subdir-y += lorax
subdir-y += rpm
subdir-$(call is_os,ubuntu) += ubuntu
