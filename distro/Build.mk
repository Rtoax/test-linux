include apt.mk
include anaconda.mk
include flatpak.mk
include os.mk
include rpm.mk
include lorax.mk
include dpkg.mk

subdir-$(call is_os,alpine) += alpine
subdir-${HAVE_ANACONDA} += anaconda
subdir-${HAVE_APT} += apt
subdir-${HAVE_DPKG} += dpkg
subdir-${HAVE_FLATPAK} += flatpak
subdir-${HAVE_LORAX} += lorax
subdir-${HAVE_RPM} += rpm
subdir-$(call is_os,ubuntu) += ubuntu
