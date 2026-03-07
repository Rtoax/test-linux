# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# see also /usr/include/bits/signum-generic.h
#

ifndef	_BITS_SIGNUM_GENERIC_MK
export _BITS_SIGNUM_GENERIC_MK = 1


# ISO C99 signals.
SIGINT		= 2	# Interactive attention signal.
SIGILL		= 4	# Illegal instruction.
SIGABRT		= 6	# Abnormal termination.
SIGFPE		= 8	# Erroneous arithmetic operation.
SIGSEGV		= 11	# Invalid access to storage.
SIGTERM		= 15	# Termination request.

# Historical signals specified by POSIX. */
SIGHUP		= 1	# Hangup.
SIGQUIT		= 3	# Quit.
SIGTRAP		= 5	# Trace/breakpoint trap.
SIGKILL		= 9	# Killed.
SIGPIPE		= 13	# Broken pipe.
SIGALRM		= 14	# Alarm clock.

# Archaic names for compatibility.
SIGIO		= ${SIGPOLL}	# I/O now possible (4.2 BSD).
SIGIOT		= ${SIGABRT}	# IOT instruction, abort() on a PDP-11.
SIGCLD		= ${SIGCHLD}	# Old System V name */

# Include system specific bits.
include bits/signum-arch.mk

# Biggest signal number + 1 (including real-time signals).
_NSIG		= $(shell expr ${__SIGRTMAX} + 1)

ifdef DEBUG
  $(info _NSIG = ${_NSIG})
endif

endif
