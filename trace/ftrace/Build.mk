include trace-cmd.mk

subdir-y += samples
subdir-y += scripts
subdir-${HAVE_TRACE_CMD} += trace-cmd

prog-y += README.sh
