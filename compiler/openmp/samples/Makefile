# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk


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
TARGETS += omp_get_max_threads
TARGETS += omp_set_num_threads
TARGETS += omp_get_num_procs
TARGETS += omp_get_nested
TARGETS += omp_set_nested_1
TARGETS += omp_set_nested_2
TARGETS += omp_set_nest_lock
TARGETS += omp_destroy_nest_lock
TARGETS += omp_set_lock
TARGETS += omp_test_lock
TARGETS += omp_test_nest_lock
TARGETS += omp_set_max_active_levels
TARGETS += omp_in_parallel
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
TARGETS += omp_get_active_level
TARGETS += omp_get_ancestor_thread_num
TARGETS += omp_get_schedule
TARGETS += omp_get_level
TARGETS += omp_get_thread_limit
TARGETS += omp_get_team_size
TARGETS += omp_get_wtick

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -O0
CFLAGS += -fopenmp
CFLAGS += -Wno-error=unused-variable

ifdef DEBUG
  CFLAGS += -g -ggdb
endif

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

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
omp_get_thread_limit: omp_get_thread_limit.o
omp_get_num_procs: omp_get_num_procs.o
omp_get_level: omp_get_level.o
omp_get_thread_num: omp_get_thread_num.o
omp_get_max_threads: omp_get_max_threads.o
omp_set_num_threads: omp_set_num_threads.o
omp_get_nested: omp_get_nested.o
omp_set_nested_1: omp_set_nested_1.o
omp_set_nested_2: omp_set_nested_2.o
omp_set_nest_lock: omp_set_nest_lock.o
omp_set_lock: omp_set_lock.o
omp_test_lock: omp_test_lock.o
omp_test_nest_lock: omp_test_nest_lock.o
omp_destroy_nest_lock: omp_destroy_nest_lock.o
omp_set_max_active_levels: omp_set_max_active_levels.o
omp_get_active_level: omp_get_active_level.o
omp_in_parallel: omp_in_parallel.o
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
omp_get_ancestor_thread_num: omp_get_ancestor_thread_num.o
omp_get_schedule: omp_get_schedule.o
omp_get_team_size: omp_get_team_size.o
omp_get_wtick: omp_get_wtick.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
