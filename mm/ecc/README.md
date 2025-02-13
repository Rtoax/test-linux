ECC - Error Checking and Correcting
===================================

DRAM（Dynamic Random Access Memory），即动态随机存取存储器，最为常见的系统内存。
ECC是“Error Checking and Correcting”的简写，中文名称是“错误检查和纠正”。
ECC内存，即应用了能够实现错误检查和纠正技术（ECC）的内存条。


EDAC - Error Detection And Correction
=====================================

EDAC，即Error Detection And Correction（错误检测与纠正）。

CE/UE
=====

内存有两种错误类型分别是CE和UE

* `CE`是`Correctable Error`的简称
* `UE`是`Uncorrectable Error`的简称

`CE`即可恢复的错误，暂不影响系统的正常运行，可以在找时机停机换掉。
`UE`为不可恢复的内存错误，通常会导致宕机。

# devices

* /sys/devices/system/edac/mc


# Reed-Solomon编码

- [Reed–Solomon error-correcting code decoder](https://www.nayuki.io/page/reed-solomon-error-correcting-code-decoder)
