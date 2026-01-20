target-y := perf_event_open
target-y += perf_event_open-2

# TODO: why? see commit ca1f62592166 ("perf_event_open-2.c: why error: ‘ptr’ may be used uninitialized???")
CFLAGS_perf_event_open-2 := -Wno-error=maybe-uninitialized

include main.mk

perf_event_open: perf_event_open.o perf_helpers.o
perf_event_open-2: perf_event_open-2.o perf_helpers.o
