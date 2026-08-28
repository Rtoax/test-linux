include anaconda.mk

subdir-y += alpine
subdir-${HAVE_ANACONDA} += anaconda
subdir-y += apt
subdir-y += dpkg
subdir-y += flatpak
subdir-y += lorax
subdir-y += rpm
