# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# see also /usr/include/bits/signum-arch.h
#

ifndef _BITS_SIGNUM_ARCH_MK
_BITS_SIGNUM_ARCH_MK = 1

SIGSTKFLT	= 16	# Stack fault (obsolete).
SIGPWR		= 30	# Power failure imminent.

# Historical signals specified by POSIX. */
SIGBUS		=  7	# Bus error.
SIGSYS		= 31	# Bad system call.

# New(er) POSIX signals (1003.1-2008, 1003.1-2013).
SIGURG		= 23	# Urgent data is available at a socket.
SIGSTOP		= 19	# Stop, unblockable.
SIGTSTP		= 20	# Keyboard stop.
SIGCONT		= 18	# Continue.
SIGCHLD		= 17	# Child terminated or stopped.
SIGTTIN		= 21	# Background read from control terminal.
SIGTTOU		= 22	# Background write to control terminal.
SIGPOLL		= 29	# Pollable event occurred (System V).
SIGXFSZ		= 25	# File size limit exceeded.
SIGXCPU		= 24	# CPU time limit exceeded.
SIGVTALRM	= 26	# Virtual timer expired.
SIGPROF		= 27	# Profiling timer expired.
SIGUSR1		= 10	# User-defined signal 1.
SIGUSR2		= 12	# User-defined signal 2.

# Nonstandard signals found in all modern POSIX systems
# (including both BSD and Linux).
SIGWINCH	= 28	# Window size change (4.3 BSD, Sun).

# Archaic names for compatibility.
SIGIO		= ${SIGPOLL}	# I/O now possible (4.2 BSD).
SIGIOT		= ${SIGABRT}	# IOT instruction, abort() on a PDP-11.
SIGCLD		= ${SIGCHLD}	# Old System V name */

__SIGRTMIN	= 32
__SIGRTMAX	= 64

endif
