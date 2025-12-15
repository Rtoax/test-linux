
* [https://lwn.net/Articles/383362/](https://lwn.net/Articles/383362/)


Usage:

```bash
   [mod] # insmod sillymod-event.ko
   [mod] # cd /sys/kernel/debug/tracing
   [tracing] # ls events
   block   ext4    header_event  i915  jbd2  module  sched  skb       timer
   enable  ftrace  header_page   irq   kmem  power   silly  syscalls  workqueue
   [tracing] # ls events/silly
   enable  filter  me_silly
   [tracing] # echo 1 > events/silly/me_silly/enable
   [tracing] # cat trace
   # tracer: nop
   #
   #           TASK-PID    CPU#    TIMESTAMP  FUNCTION
   #              | |       |          |         |
       silly-thread-5377  [000]  1802.845581: me_silly: time=4304842209 count=10
       silly-thread-5377  [000]  1803.845008: me_silly: time=4304843209 count=11
       silly-thread-5377  [000]  1804.844451: me_silly: time=4304844209 count=12
       silly-thread-5377  [000]  1805.843886: me_silly: time=4304845209 count=13
```

LWN original article 
=========================

* [https://lwn.net/Articles/383362/](https://lwn.net/Articles/383362/)

Using the TRACE_EVENT() macro (Part 3)
April 21, 2010

This article was contributed by Steven Rostedt

Tracepoints within the kernel facilitate the analysis of how the kernel performs. The flow of critical information can be followed and examined in order to debug a latency problem, or to simply figure out better ways to tune the system. The core kernel tracepoints, like the scheduler and interrupt tracepoints, let the user see when and how events take place inside the kernel. Module developers can also take advantage of tracepoints; if their users or customers have problems, the developer can have them enable the tracepoints and analyze the situation. This article will explain how to add tracepoints in modules that are outside of the core kernel code.

In Part 1, the process of creating a tracepoint in the core kernel was explained. Part 2 explained how to consolidate tracepoints with the use of DECLARE_EVENT_CLASS() and DEFINE_EVENT() and went over the field macros of TP_STRUCT__entry, and the function helpers of TP_printk(). This article takes a look at how to add tracepoints outside of the core kernel, which can be used by modules or architecture specific code. A brief look at some of the magic behind the TRACE_EVENT() macro, and a few more examples to get your feet wet with using tracepoints.

Defining a trace header outside of include/trace/events
For tracepoints in modules or in architecture-specific directories, having trace header files in the global include/trace/events directory may clutter it. The result would be to put files like mips_cpu.h or arm_cpu.h, which are not necessary for the core kernel, into that directory. It would end up something like the old include/asm-*/ setup. Also, if tracepoints went into staging drivers, putting staging header files in the core kernel code base would be a bad design.

Because trace header files are handled very differently than other header files, the best solution is to have the header files placed at the location where they are used. For example, the XFS tracepoints are located in the XFS subdirectory in fs/xfs/xfs_trace.h. But, some of the magic of define_trace.h is that it must be able to include the trace file that included it (the reason for TRACE_HEADER_MULTI_READ). As explained in Part 1, the trace header files start with the cpp conditional:

   #if !defined(_TRACE_SCHED_H) || defined(TRACE_HEADER_MULTI_READ)
   #define _TRACE_SCHED_H
Part 1 explained that one and only one of the C files that include a particular trace header will define CREATE_TRACE_POINTS before including the trace header. That activates the define_trace.h that the trace header file includes. The define_trace.h file will include the header again, but will first define TRACE_HEADER_MULTI_READ. As the cpp condition shows, this define will allow the contents of the trace header to be read again.

For define_trace.h to include the trace header file, it must be able to find it. To do this, some changes need to be made to the Makefile where the trace file is included, and that file will need to tell define_trace.h not to look for it in the default location (include/trace/events).

To tell define_trace.h where to find the trace header, the Makefile must define the path to the location of the trace file. One method is to extend CFLAGS to include the path:

    EXTRA_CFLAGS = -I$(src)
But that affects CFLAGS for all files that the Makefile builds. If it is desired to only modify the the CFLAGS for the C file that has the CREATE_TRACE_POINTS defined, then the method used by the net/mac80211/Makefile can be used:

   CFLAGS_driver-trace.o = -I$(src)
The driver-trace.c file contains the CREATE_TRACE_POINTS define and the include of driver-trace.h that contains the TRACE_EVENT() macros for the mac80211 tracepoints.

To demonstrate how to add tracepoints to a module, I wrote a simple module, called sillymod, which just creates a thread that wakes up every second and performs a printk and records the number of times that it has done so. I will look at the relevant portions of the files, but the full file contents are also available: module, Makefile, the module with tracepoint, and the trace header file.

The first step is to create the desired tracepoints. The trace header file is created the same way as the core trace headers described in Part 1, with a few more additions. The header must start by defining the system where all tracepoints within the file will belong to:

   #undef TRACE_SYSTEM
   #define TRACE_SYSTEM silly
This module creates a trace system called silly. Then the special cpp condition is included:

   #if !defined(_SILLY_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
   #define _SILLY_TRACE_H
The linux/tracepoint.h file is included, and finally the TRACE_EVENT() macros; one in this example:

   #include <linux/tracepoint.h>

   TRACE_EVENT(me_silly,

	TP_PROTO(unsigned long time, unsigned long count),

	TP_ARGS(time, count),

	TP_STRUCT__entry(
		__field(	unsigned long,	time	)
		__field(	unsigned long,	count	)
	),

	TP_fast_assign(
		__entry->time = jiffies;
		__entry->count = count;
	),

	TP_printk("time=%lu count=%lu", __entry->time, __entry->count)
   );

   #endif /* _SILLY_TRACE_H */
The above is the same as what was described in Part 1 for core kernel tracepoints. After the #endif things become a bit different. Before including the define_trace.h file the following is added:

   /* This part must be outside protection */
   #undef TRACE_INCLUDE_PATH
   #define TRACE_INCLUDE_PATH .
   #define TRACE_INCLUDE_FILE silly-trace
   #include <trace/define_trace.h>
The TRACE_INCLUDE_PATH tells define_trace.h not to look in the default location (include/trace/events) for the trace header, but instead look in the include search path. By default, define_trace.h will include a file defined by TRACE_SYSTEM. The TRACE_INCLUDE_FILE tells define_trace.h that the trace header is called silly-trace.h (The .h is automatically added to the end of TRACE_INCLUDE_PATH).

To add the tracepoint to the module, the module now includes the trace header. Before including the trace header it must also define CREATE_TRACE_POINTS:

   #define CREATE_TRACE_POINTS
   #include "silly-trace.h"
The tracepoint can now be added to the code.

    set_current_state(TASK_INTERRUPTIBLE);
    schedule_timeout(HZ);
    printk("hello! %lu\n", count);
    trace_me_silly(jiffies, count);
    count++;
Finally the Makefile must set the CFLAGS to have the includes include the local directory where the silly-trace.h file resides.

   CFLAGS_sillymod-event.o = -I$(src)
One might believe the following would also work without modifying the Makefile, if the module resided in the kernel tree:

   #define TRACE_INCLUDE_PATH ../../path/to/trace/header
Using a path name in TRACE_INCLUDE_PATH other than '.' runs the risk of containing a macro. For example, if XFS defined TRACE_INCLUDE_PATH as ../../fs/xfs/linux-2.6/xfs_trace.h, it would fail. That is because the Linux build #defines the name linux to nothing, which would make the path be ../../fs/xfs/-2.6/xfs_trace.h.

Now the trace event is available.

   [mod] # insmod sillymod-event.ko
   [mod] # cd /sys/kernel/debug/tracing
   [tracing] # ls events
   block   ext4    header_event  i915  jbd2  module  sched  skb       timer
   enable  ftrace  header_page   irq   kmem  power   silly  syscalls  workqueue
   [tracing] # ls events/silly
   enable  filter  me_silly
   [tracing] # echo 1 > events/silly/me_silly/enable
   [tracing] # cat trace
   # tracer: nop
   #
   #           TASK-PID    CPU#    TIMESTAMP  FUNCTION
   #              | |       |          |         |
       silly-thread-5377  [000]  1802.845581: me_silly: time=4304842209 count=10
       silly-thread-5377  [000]  1803.845008: me_silly: time=4304843209 count=11
       silly-thread-5377  [000]  1804.844451: me_silly: time=4304844209 count=12
       silly-thread-5377  [000]  1805.843886: me_silly: time=4304845209 count=13
Once define_trace.h file can safely locate the trace header, the module's tracepoints can be created. To understand why all this manipulation is needed, a look at how define_trace.h is implemented may clarify things a bit.

A look inside the magic of TRACE_EVENT()
For those that dare to jump into the mystical world of the C preprocessor, take a look into include/trace/ftrace.h. But be warned, what you find there may leave you a bit loony, or at least think that the ones that wrote that code were a bit loony (in which case, you may be right). The include/trace/define_trace.h file does some basic set up for the TRACE_EVENT() macro, but for a trace to take advantage of it, it must have a header file in define_trace.h to do the real work (as do Ftrace and perf).

cpp tricks and treats
While I was working on my Masters, a professor showed me a trick with cpp that lets one map strings to enums using the same data:

   #define DOGS { C(JACK_RUSSELL), C(BULL_TERRIER), C(ITALIAN_GREYHOUND) }
   #undef C
   #define C(a) ENUM_##a
   enum dog_enums DOGS;
   #undef C
   #define C(a) #a
   char *dog_strings[] = DOGS;
   char *dog_to_string(enum dog_enums dog)
   {
           return dog_strings[dog];
   }
The trick is that the macro DOGS contains a sub-macro C() that we can redefine and change the behavior of DOGS. This concept is key to how the TRACE_EVENT() macro works. All the sub-macros within TRACE_EVENT() can be redefined and cause the TRACE_EVENT() to be used to create different code that uses the same information. Part 1 described the requirements needed to create a tracepoint. One set of data (in the TRACE_EVENT() definition) must be able to do several things. Using this cpp trick, it is able to accomplish just that.

The tracepoint code created by Mathieu Desnoyers required a DECLARE_TRACE(name, proto, args) be defined in a header file, and in some C file DEFINE_TRACE(name) was used. TRACE_EVENT() now does both jobs. In include/linux/tracepoint.h:

   #define TRACE_EVENT(name, proto, args, struct, assign, print)	\
        DECLARE_TRACE(name, PARAMS(proto), PARAMS(args))
The PARAMS() macro lets proto and args contain commas and not be mistaken as multiple parameters of DECLARE_TRACE(). Since the tracepoint.h must be included in all trace headers, this makes the TRACE_EVENT() macro fulfill the first part of the tracepoint creation. When a C file defines CREATE_TRACE_POINTS before including a trace header, the define_trace.h becomes active and performs:

   #undef TRACE_EVENT
   #define TRACE_EVENT(name, proto, args, tstruct, assign, print)	\
        DEFINE_TRACE(name)
That is not enough, however, because the define_trace.h is declared after the TRACE_EVENT() macros are used. For this code to have an impact, the TRACE_EVENT() macro must be included again. The define_trace.h does some nasty C preprocessor obfuscation to be able to include the file that just included it:

   #define TRACE_HEADER_MULTI_READ
   #include TRACE_INCLUDE(TRACE_INCLUDE_FILE)
The defining of the TRACE_HEADER_MULTI_READ will let the trace header be read again (and this is why it is needed in the first place). The TRACE_INCLUDE(TRACE_INCLUDE_FILE) is more cpp macro tricks that will include the file that included it. As explained in previous articles, this macro will use either TRACE_SYSTEM.h or TRACE_INCLUDE_FILE.h if that is defined, and will include the file from include/trace/events/ if TRACE_INCLUDE_PATH is not defined. I'll spare the reader the ugliness of the macros to accomplish this. For the more masochistic reader, feel free to look at the include/trace/define_trace.h file directly. When the file is included again, the TRACE_EVENT() macro will be processed again, but with its new meaning.

The above explains how tracepoints are created. It only creates the tracepoint itself, and it does nothing to add it to a tracer's infrastructure. For Ftrace, this is where the ftrace.h file inside the define_trace.h comes into play. (Warning, the ftrace.h file is even more bizarre than define_trace.h). The macros in ftrace.h create the files and directories found in tracing/events. ftrace.h uses the same tricks explained earlier of redefining the macros within the TRACE_EVENT() macro as well as redefining the TRACE_EVENT() macro itself. How ftrace.h works is beyond the scope of this article, but feel free to read it directly, if you don't have any allergies to backslashes.

Playing with trace events
If you change directories to the debugfs filesystem mount point (usually /sys/kernel/debug) and take a look inside tracing/events you will see all of the trace event systems defined in your kernel (i.e. the trace headers that defined TRACE_SYSTEM).

   [tracing] # ls events
   block  enable  ftrace  header_event  header_page  irq       kmem  module
   power  sched   skb     syscalls      timer        workqueue
As mentioned in Part 2, the enable files are used to enable a tracepoint. The enable file in the events directory can enable or disable all events in the system, the enable file in one of the system's directories can enable or disable all events within the system, and the enable file within the specific event directory can enable or disable that event.

Note, by writing '1' into any of the enable files will enable all events within that directory and below. Writing a '0' will disable all events within that directory and below.

One nice feature about events is that they also show up in the Ftrace tracers. If an event is enabled while a tracer is running, those events will show up in the trace. Enabling events can make the function tracer even more informative:

   [tracing] # echo 1 > events/sched/enable
   [tracing] # echo function > current_tracer
   [tracing] # head -15 trace
   # tracer: function
   #
   #           TASK-PID    CPU#    TIMESTAMP  FUNCTION
   #              | |       |          |         |
               Xorg-1608  [001]  1695.236400: task_of <-update_curr
               Xorg-1608  [001]  1695.236401: sched_stat_runtime: task: Xorg:1608 runtime: 402851 [ns], vruntime: 153144994503 [ns]
               Xorg-1608  [001]  1695.236402: account_group_exec_runtime <-update_curr
               Xorg-1608  [001]  1695.236402: list_add <-enqueue_entity
               Xorg-1608  [001]  1695.236403: place_entity <-enqueue_entity
               Xorg-1608  [001]  1695.236403: task_of <-enqueue_entity
               Xorg-1608  [001]  1695.236404: sched_stat_sleep: task: gnome-terminal:1864 sleep: 639071 [ns]
               Xorg-1608  [001]  1695.236405: __enqueue_entity <-enqueue_entity
               Xorg-1608  [001]  1695.236406: hrtick_start_fair <-enqueue_task_fair
               Xorg-1608  [001]  1695.236407: sched_wakeup: task gnome-terminal:1864 [120] success=1 [001]
               Xorg-1608  [001]  1695.236408: check_preempt_curr <-try_to_wake_up
Combining the events with tricks from the function graph tracer, we can find interrupt latencies, and which interrupts are responsible for long latencies.

   [tracing] # echo do_IRQ > set_ftrace_filter
   [tracing] # echo 1 > events/irq/irq_handler_entry/enable
   [tracing] # echo function_graph > current_tracer
   [tracing] # cat trace
   # tracer: function_graph
   #
   # CPU  DURATION                  FUNCTION CALLS
   # |     |   |                     |   |   |   |
    0)   ==========> |
    0)               |  do_IRQ() {
    0)               |  /* irq_handler_entry: irq=30 handler=iwl3945 */
    0)   ==========> |
    0)               |    do_IRQ() {
    0)               |      /* irq_handler_entry: irq=30 handler=iwl3945 */
    0) + 22.965 us   |    }
    0)   <========== |
    0) ! 148.135 us  |  }
    0)   <========== |
    0)   ==========> |
    0)               |  do_IRQ() {
    0)               |  /* irq_handler_entry: irq=1 handler=i8042 */
    0) + 45.347 us   |  }
    0)   <========== |
Writing do_IRQ into set_ftrace_filter makes the function tracer only trace the do_IRQ() function. Then the irq_handler_entry tracepoint is activated and the function_graph tracer is selected. Since the function graph tracer shows the time a function executed, we can see the how long the interrupts ran for. But the function graph tracer only shows that the do_IRQ() function ran, but not which interrupt it executed. By enabling the irq_handler_entry event, we now see which interrupt was running. The above shows that my laptop's iwl3945 interrupt that handles the wireless communication caused a 148 microsecond latency!

Conclusion
Tracepoints are a very powerful tool, but to make them useful, they must be flexible and trivial to add. Adding TRACE_EVENT() macros are quite easy and they are popping up all over the kernel. The 2.6.34-rc3 kernel currently has over 300 TRACE_EVENT() macros defined; 341 as of this writing.

The code to implement the trace events uses lots of cpp tricks to accomplish its task. But the complexity of the implementation simplified the usage of tracepoints. The rule of thumb in creating the TRACE_EVENT() macro was: make the use of the TRACE_EVENT() macro as simple as possible, even if that makes the implementation of it extremely complex. Sometimes, the easier something is to use, the more complexity there is to create it. Now, a developer does not need to know how the TRACE_EVENT() macro works, she or he only needs to know that the work has been done for them. Adding TRACE_EVENT()s are easy, and any developer can now take advantage of them.


