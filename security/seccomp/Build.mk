include libseccomp.mk

subdir-y := samples
subdir-${HAVE_LIBSECCOMP} += libseccomp
