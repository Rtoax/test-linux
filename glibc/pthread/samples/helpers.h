#pragma once

/**
 * @cpu_list: The cpu list should like 1-3,6
 */
int taskset(int pid, char *cpu_list);

