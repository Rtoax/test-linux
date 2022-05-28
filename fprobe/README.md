Fprobe - Function entry/exit probe
==================================

* [https://www.kernel.org/doc/html/latest/trace/fprobe.html](https://www.kernel.org/doc/html/latest/trace/fprobe.html)

Fprobe is a function entry/exit probe mechanism based on ftrace. Instead of using ftrace full feature, if you only want to attach callbacks on function entry and exit, similar to the kprobes and kretprobes, you can use fprobe. Compared with kprobes and kretprobes, fprobe gives faster instrumentation for multiple functions with single handler. This document describes how to use fprobe.
