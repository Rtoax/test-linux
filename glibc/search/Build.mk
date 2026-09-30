target-y += hsearch
target-y += lfind
target-y += queue
target-y += tsearch

# Examples:
target-y += id-handler

CFLAGS_id-handler := -DTEST_MAIN=1

prog-y += ${target-y}
