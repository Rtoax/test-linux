KVM - Kernel Virtual Machine
============================

* [https://www.linux-kvm.org/page/Main_Page](https://www.linux-kvm.org/page/Main_Page)

KVM (for Kernel-based Virtual Machine) is a full virtualization solution for Linux on x86 hardware containing virtualization extensions (Intel VT or AMD-V). It consists of a loadable kernel module, kvm.ko, that provides the core virtualization infrastructure and a processor specific module, kvm-intel.ko or kvm-amd.ko.

Using KVM, one can run multiple virtual machines running unmodified Linux or Windows images. Each virtual machine has private virtualized hardware: a network card, disk, graphics adapter, etc.

> KVM type-1 hypervisor.


# Memory Virtualization

- GVA
- GPA (IPA in arm)
- HVA
- HPA


# vCPU

## KVM 支持的 CPU modules

- Host passthrough
- Custom (Named model)
- Host model

查看Host支持的cpu-modules

```bash
$ sudo virsh cpu-models x86_64
```


# x86 vAPIC

TODO


# Devices

- IOMMU: x86
	- iommu: AMD
	- VT-d: Intel
- SMMU: arm

