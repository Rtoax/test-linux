// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */

#ifndef trigger
# error Must define trigger
#endif

trigger('0', "loglevel 0 (emergency)");
trigger('1', "loglevel 1 (alert)");
trigger('2', "loglevel 2 (critical)");
trigger('3', "loglevel 3 (error)");
trigger('4', "loglevel 4 (warning)");
trigger('5', "loglevel 5 (notice)");
trigger('6', "loglevel 6 (info)");
trigger('7', "loglevel 7 (debug)");
trigger('8', "loglevel 8");
trigger('9', "loglevel 9");
trigger('b', "reboot");
trigger('c', "crash");
trigger('e', "terminate all tasks");
trigger('f', "memory full OOM kill");
/* g: May be registered for the kernel debugger */
trigger('g', "kernel debugger");
/* h: reserved for help */
trigger('h', "help");
trigger('i', "Kill all tasks");
trigger('j', "thaw filesystems");
trigger('k', "sak");
trigger('l', "show basktrace all active cpus");
trigger('m', "show memory usage");
trigger('n', "nice all RT tasks");
/* o: This will often be registered as 'Off' at init time */
trigger('o', "poweroff");
trigger('p', "show registers");
trigger('q', "show all timers");
trigger('r', "unraw");
trigger('s', "sync");
trigger('t', "show task states");
trigger('u', "unmount");
trigger('v', "force fb");
trigger('w', "show blocked tasks");
trigger('z', "dump ftrace buffer");
