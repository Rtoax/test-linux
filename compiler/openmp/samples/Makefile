# SPDX-License-Identifier: GPL-3.0

OUTPUT := .output/

targets :=
targets += atomic
targets += barrier
targets += critical
targets += default
targets += firstprivate
targets += flush
targets += lastprivate
targets += lock
targets += master
targets += memory
targets += nowait
targets += omp_get_thread_num
targets += omp_get_max_threads
targets += omp_set_num_threads
targets += omp_get_num_procs
targets += omp_get_nested
targets += omp_set_nested_1
targets += omp_set_nested_2
targets += omp_set_nest_lock
targets += omp_destroy_nest_lock
targets += omp_set_lock
targets += omp_test_lock
targets += omp_test_nest_lock
targets += omp_set_max_active_levels
targets += omp_in_parallel
targets += ordered
targets += parallel_for
targets += pragma_omp_atomic
targets += pragma_omp_barrier
targets += pragma_omp_critical
targets += pragma_omp_parallel_copyin
targets += pragma_omp_parallel_for_reduction
targets += private
targets += private_firstprivate_lastprivate_threadprivate
targets += reduction
targets += schedule_dynamic
targets += schedule_guided
targets += schedule_runtime
targets += schedule_sections_single_master_nowait
targets += schedule_static
targets += sections_section
targets += shared
targets += simd
targets += single
targets += threadprivate
targets += threadprivate_copyin
targets += threadprivate_copyprivate
targets += omp_get_active_level
targets += omp_get_ancestor_thread_num
targets += omp_get_schedule
targets += omp_get_level
targets += omp_get_thread_limit
targets += omp_get_team_size
targets += omp_get_wtick

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
