LTO - Link-Time Opemizations
==============================

* https://gcc.gnu.org/wiki/LinkTimeOptimization


GCC implements two link-time compilation modes
----------------------------------------------

- https://gcc.gnu.org/onlinedocs/gccint/LTO-Overview.html

1. LTO mode: in which the whole program is read into the compiler at link-time and optimized in a similar way as if it were a single source-level compilation unit.
2. WHOPR or partitioned mode: designed to utilize multiple CPUs and/or a distributed compilation environment to quickly link large applications.
    a. WHOPR stands for WHOle Program optimizeR
    b. It partitions the aggregated callgraph from many different .o files and distributes the compilation of the sub-graphs to different CPUs.


WHOPR splits LTO into three main stages
---------------------------------------

1. Local generation (LGEN)
2. Whole Program Analysis (WPA)
3. Local transformations (LTRANS)

Local generation (LGEN)
~~~~~~~~~~~~~~~~~~~~~~~

This stage executes in parallel. Every file in the program is compiled into the intermediate language and packaged together with the local call-graph and summary information. This stage is the same for both the LTO and WHOPR compilation mode.

Whole Program Analysis (WPA)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Whole Program Analysis (WPA) WPA is performed sequentially. The global call-graph is generated, and a global analysis procedure makes transformation decisions. The global call-graph is partitioned to facilitate parallel optimization during phase 3. The results of the WPA stage are stored into new object files which contain the partitions of program expressed in the intermediate language and the optimization decisions.

Local transformations (LTRANS)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This stage executes in parallel. All the decisions made during phase 2 are implemented locally in each partitioned object file, and the final object code is generated. Optimizations which cannot be decided efficiently during the phase 2 may be performed on the local call-graph partitions.

LLVM Link Time Optimization: Design and Implementation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

see `llvm/` directory.

* https://llvm.org/docs/LinkTimeOptimization.html

Why in the Linker?
~~~~~~~~~~~~~~~~~~

* https://gcc.gnu.org/wiki/whopr/driver

As of this writing, the pre-ld driver collect2 performs the LTO file identification. However, this is sub-optimal. The benefits of driving LTO from the linker are:

* The linker performs full symbol resolution. Therefore, it will only bring in objects that are necessary. This can greatly reduce build and library extraction times.
* Several build systems use ld -r to build components and/or shared libraries.
* The linker properly handles archives
* The linker knows which functions and globals are externally referenced. `LLVM's IPA <http://llvm.org/docs/LinkTimeOptimization.html>`_ page provides an extended example on why the integration in the linker is necessary to perform precise dead function elimination. The same chain of arguments holds for globals. LTO needs to know about externally referenced symbols.
* Less work - currently, collect2 needs to fork/exec 'nm' on every input file to determine whether it contains IR, which is not optimal.


Links
-----

- https://gcc.gnu.org/wiki/LinkTimeOptimization
- https://gcc.gnu.org/wiki/LTO_Representation_Changes
