target-y += posix_spawn

prog-y += ${target-y}

LDFLAGS := -pthread
