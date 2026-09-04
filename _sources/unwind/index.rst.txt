UNWind
======

.. toctree::
   :maxdepth: 1

   abbrev
   libunwind


CFI - Call Frame Information
----------------------------

`.cfi_sections` 用来描述产生的目标是 `.eh_frame`
`.cfi_startproc` 每个函数入口处
`.cfi_endproc` 函数结尾处，与 `.cfi_startproc` 对应


eh_frame
--------

`.eh_frame` 节是一种特殊的节，用于存储程序的调试信息和堆栈回溯相关的信息。


Links
-----

- `Unwind 栈回溯详解：libunwind <https://blog.csdn.net/Rong_Toa/article/details/110846509>`_
