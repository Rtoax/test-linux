Qemu - Quick Emulator
======================

A generic and open source machine emulator and virtualizer.


# Accelerators

## Initialization

```
qemu_init() {
  configure_accelerators() {
    /* config -accel: kvm or tcg */
    do_configure_accelerator() {
      accel_init_machine() {
        /**
         * kvm: kvm_init();
         * tcg: tcg_init_machine();
         */
        acc->init_machine();
      }
    }
  }
}
```


# Links

* [https://www.qemu.org/](https://www.qemu.org/)
* [GitLab](https://gitlab.com/qemu-project/qemu)
* [GitHub Readonly Mirror](https://github.com/qemu/QEMU)

