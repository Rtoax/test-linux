target-y += hsearch
target-y += lfind
target-y += queue
target-y += tsearch

# Examples:
target-y += fd-handler

CFLAGS_fd-handler := -DTEST_MAIN=1

prog-y += ${target-y}
