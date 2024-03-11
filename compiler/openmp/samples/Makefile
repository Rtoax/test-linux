
TARGETS :=
TARGETS += atomic
TARGETS += barrier
TARGETS += critical
TARGETS += default
TARGETS += firstprivate
TARGETS += flush
TARGETS += lastprivate
TARGETS += lock
TARGETS += master
TARGETS += memory
TARGETS += nowait
TARGETS += omp_get_thread_num
TARGETS += omp_set_num_threads
TARGETS += omp_set_nested_1
TARGETS += omp_set_nested_2
TARGETS += omp_set_nest_lock
TARGETS += ordered
TARGETS += parallel_for
TARGETS += pragma_omp_atomic
TARGETS += pragma_omp_barrier
TARGETS += pragma_omp_critical
TARGETS += pragma_omp_parallel_copyin
TARGETS += pragma_omp_parallel_for_reduction
TARGETS += private
TARGETS += private_firstprivate_lastprivate_threadprivate
TARGETS += reduction
TARGETS += schedule_dynamic
TARGETS += schedule_guided
TARGETS += schedule_runtime
TARGETS += schedule_sections_single_master_nowait
TARGETS += schedule_static
TARGETS += sections_section
TARGETS += shared
TARGETS += simd
TARGETS += single
TARGETS += threadprivate
TARGETS += threadprivate_copyin
TARGETS += threadprivate_copyprivate

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -O0
CFLAGS += -fopenmp
CFLAGS += -Wno-error=unused-variable

ifdef DEBUG
CFLAGS += -g -ggdb
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
atomic: atomic.o
barrier: barrier.o
critical: critical.o
default: default.o
firstprivate: firstprivate.o
flush: flush.o
lastprivate: lastprivate.o
lock: lock.o
master: master.o
memory: memory.o
nowait: nowait.o
omp_get_thread_num: omp_get_thread_num.o
omp_set_num_threads: omp_set_num_threads.o
omp_set_nested_1: omp_set_nested_1.o
omp_set_nested_2: omp_set_nested_2.o
omp_set_nest_lock: omp_set_nest_lock.o
ordered: ordered.o
parallel_for: parallel_for.o
pragma_omp_atomic: pragma_omp_atomic.o
pragma_omp_barrier: pragma_omp_barrier.o
pragma_omp_critical: pragma_omp_critical.o
pragma_omp_parallel_copyin: pragma_omp_parallel_copyin.o
pragma_omp_parallel_for_reduction: pragma_omp_parallel_for_reduction.o
private: private.o
private_firstprivate_lastprivate_threadprivate: private_firstprivate_lastprivate_threadprivate.o
reduction: reduction.o
schedule_dynamic: schedule_dynamic.o
schedule_guided: schedule_guided.o
schedule_runtime: schedule_runtime.o
schedule_sections_single_master_nowait: schedule_sections_single_master_nowait.o
schedule_static: schedule_static.o
sections_section: sections_section.o
shared: shared.o
single: single.o
simd: simd.o
threadprivate: threadprivate.o
threadprivate_copyin: threadprivate_copyin.o
threadprivate_copyprivate: threadprivate_copyprivate.o


%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
