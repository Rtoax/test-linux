target-y := pthread_self

prog-y += ${target-y}

LDFLAGS := -pthread
