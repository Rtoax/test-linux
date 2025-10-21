# SPDX-License-Identifier: GPL-3.0

OUTPUT := .output/

target-y :=
target-y += atomic
target-y += barrier
target-y += critical
target-y += default
target-y += firstprivate
target-y += flush
target-y += lastprivate
target-y += lock
target-y += master
target-y += memory
target-y += nowait
target-y += omp_get_thread_num
target-y += omp_get_max_threads
target-y += omp_set_num_threads
target-y += omp_get_num_procs
target-y += omp_get_nested
target-y += omp_set_nested_1
target-y += omp_set_nested_2
target-y += omp_set_nest_lock
target-y += omp_destroy_nest_lock
target-y += omp_set_lock
target-y += omp_test_lock
target-y += omp_test_nest_lock
target-y += omp_set_max_active_levels
target-y += omp_in_parallel
target-y += ordered
target-y += parallel_for
target-y += pragma_omp_atomic
target-y += pragma_omp_barrier
target-y += pragma_omp_critical
target-y += pragma_omp_parallel_copyin
target-y += pragma_omp_parallel_for_reduction
target-y += private
target-y += private_firstprivate_lastprivate_threadprivate
target-y += reduction
target-y += schedule_dynamic
target-y += schedule_guided
target-y += schedule_runtime
target-y += schedule_sections_single_master_nowait
target-y += schedule_static
target-y += sections_section
target-y += shared
target-y += simd
target-y += single
target-y += threadprivate
target-y += threadprivate_copyin
target-y += threadprivate_copyprivate
target-y += omp_get_active_level
target-y += omp_get_ancestor_thread_num
target-y += omp_get_schedule
target-y += omp_get_level
target-y += omp_get_thread_limit
target-y += omp_get_team_size
target-y += omp_get_wtick

CFLAGS :=  -fopenmp
CFLAGS += -Wno-error=unused-variable
LDFLAGS := -fopenmp

include ../../../template/main.mk

atomic: ${OUTPUT}atomic.o
barrier: ${OUTPUT}barrier.o
critical: ${OUTPUT}critical.o
default: ${OUTPUT}default.o
firstprivate: ${OUTPUT}firstprivate.o
flush: ${OUTPUT}flush.o
lastprivate: ${OUTPUT}lastprivate.o
lock: ${OUTPUT}lock.o
master: ${OUTPUT}master.o
memory: ${OUTPUT}memory.o
nowait: ${OUTPUT}nowait.o
omp_get_thread_limit: ${OUTPUT}omp_get_thread_limit.o
omp_get_num_procs: ${OUTPUT}omp_get_num_procs.o
omp_get_level: ${OUTPUT}omp_get_level.o
omp_get_thread_num: ${OUTPUT}omp_get_thread_num.o
omp_get_max_threads: ${OUTPUT}omp_get_max_threads.o
omp_set_num_threads: ${OUTPUT}omp_set_num_threads.o
omp_get_nested: ${OUTPUT}omp_get_nested.o
omp_set_nested_1: ${OUTPUT}omp_set_nested_1.o
omp_set_nested_2: ${OUTPUT}omp_set_nested_2.o
omp_set_nest_lock: ${OUTPUT}omp_set_nest_lock.o
omp_set_lock: ${OUTPUT}omp_set_lock.o
omp_test_lock: ${OUTPUT}omp_test_lock.o
omp_test_nest_lock: ${OUTPUT}omp_test_nest_lock.o
omp_destroy_nest_lock: ${OUTPUT}omp_destroy_nest_lock.o
omp_set_max_active_levels: ${OUTPUT}omp_set_max_active_levels.o
omp_get_active_level: ${OUTPUT}omp_get_active_level.o
omp_in_parallel: ${OUTPUT}omp_in_parallel.o
ordered: ${OUTPUT}ordered.o
parallel_for: ${OUTPUT}parallel_for.o
pragma_omp_atomic: ${OUTPUT}pragma_omp_atomic.o
pragma_omp_barrier: ${OUTPUT}pragma_omp_barrier.o
pragma_omp_critical: ${OUTPUT}pragma_omp_critical.o
pragma_omp_parallel_copyin: ${OUTPUT}pragma_omp_parallel_copyin.o
pragma_omp_parallel_for_reduction: ${OUTPUT}pragma_omp_parallel_for_reduction.o
private: ${OUTPUT}private.o
private_firstprivate_lastprivate_threadprivate: ${OUTPUT}private_firstprivate_lastprivate_threadprivate.o
reduction: ${OUTPUT}reduction.o
schedule_dynamic: ${OUTPUT}schedule_dynamic.o
schedule_guided: ${OUTPUT}schedule_guided.o
schedule_runtime: ${OUTPUT}schedule_runtime.o
schedule_sections_single_master_nowait: ${OUTPUT}schedule_sections_single_master_nowait.o
schedule_static: ${OUTPUT}schedule_static.o
sections_section: ${OUTPUT}sections_section.o
shared: ${OUTPUT}shared.o
single: ${OUTPUT}single.o
simd: ${OUTPUT}simd.o
threadprivate: ${OUTPUT}threadprivate.o
threadprivate_copyin: ${OUTPUT}threadprivate_copyin.o
threadprivate_copyprivate: ${OUTPUT}threadprivate_copyprivate.o
omp_get_ancestor_thread_num: ${OUTPUT}omp_get_ancestor_thread_num.o
omp_get_schedule: ${OUTPUT}omp_get_schedule.o
omp_get_team_size: ${OUTPUT}omp_get_team_size.o
omp_get_wtick: ${OUTPUT}omp_get_wtick.o
