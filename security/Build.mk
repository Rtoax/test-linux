# SPDX-License-Identifier: GPL-3.0
include openssl.mk

subdir-y += access
subdir-y += crypto
subdir-${HAVE_OPENSSL} += openssl
subdir-y += openssh
subdir-y += pam
subdir-y += scap
subdir-y += seccomp
subdir-y += sgx
