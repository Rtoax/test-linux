ROCm Installation
=================

# Debian

## Debian 13

```bash
$ sudo apt install -y gnupg curl wget software-properties-common
$ curl -fsSL https://repo.radeon.com/rocm/rocm.gpg.key | sudo tee /etc/apt/trusted.gpg.d/rocm.gpg
$ echo "deb [arch=amd64] https://repo.radeon.com/rocm/apt/7.0 noble main" | sudo tee /etc/apt/sources.list.d/rocm.list
$ sudo apt update
$ sudo apt install -y rocm-libs rocm-llvm
```
