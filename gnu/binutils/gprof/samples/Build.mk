target-y := foo

CFLAGS := -pg -g -ggdb -O0
LDFLAGS := -pg

target-post-y := post-foo
target-clean-y := clean-foo
