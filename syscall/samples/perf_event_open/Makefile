TARGETS += perf_event_open
TARGETS += perf_event_open-2

all: ${TARGETS}

perf_event_open: perf_event_open.o helpers.o
perf_event_open-2: perf_event_open-2.o helpers.o


clean:
	rm -f ${TARGETS} *.o
