EPT - Extended Page Table
=========================

- Intel: EPT
- AMD: NPT


# 影子页表

* `GVA -> HPA`;
* 纯软 MMU，效率很低;


# VMX EPT

* 1. `GVA -> GPA`;
* 2. `GPA -> HPA`;

> tdp: Two Dimission Page, 两级页表转换
> EPT Violation: EPT页表中缺少页表项
> GPA 在 arm64 情况下也叫 IPA(intermediate physical address)

