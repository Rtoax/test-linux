=================
Memory Management
=================

.. toctree::
   :maxdepth: 1

   abbrev
   abbrev-cim
   abbrev-memory


Process Memory Types
--------------------

见`/proc/1/smaps`

- `RSS` (Resident Set Size): 驻留内存，进程占用物理内存的大小
- `PSS` (Proportional Set Size): 如五个进程的动态库占用`50pages`，统计到一个进程的PSS为`10 Pages`
- `USS` (Unique Set Size): 仅代表进程私有内存


.. code-block:: shell

  $ sudo dnf install smem
  $ sudo apt-get install smem


Contents
--------

.. toctree::
   :maxdepth: 1

   buddy
   cache
   cma
   compaction
   cim
   damon
   dcache
   dimm
   e820
   ecc
   hbm
   hugepage
   lru
   kcompactd
   kmalloc
   kpti
   ksm
   folio
   ioremap
   memory
   memtest86+
   mmap
   numa
   pagecache
   pti
   reclaim
   rss
   slab
   smem
   swap
   tlb
   transparent_hugepage
   vmalloc
   watermark


Links
-----

- v5.8 `Memory Layout on AArch64 Linux <https://www.kernel.org/doc/html/v5.8/arm64/memory.html>`_
