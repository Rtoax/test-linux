FakeCUDA
========

# Architecture

```
    CUDA Program 1                     realCUDA
   ┌──────────────┐                ┌────────────────┐
   │cublasSgemm();│────────────────▶libcublas.so.12 │
   │              │                │                │
   └┬─────────────┘                └────────────────┘
    │
   LD_LIBRARY_PATH
    │                                                             fakeCUDA
┏━━━┿━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃   │                     Library Adaptive Layer                          ┃
┃  ┌┼──────────────────────────────────────────────────────────────────┐  ┃
┃  ││      Nvidia                  AMD                  Huawei         │  ┃
┃  ││ ┌────────────────┐     ┌───────────────┐    ┌─────────────────┐  │  ┃
┃  │└─▶libcublas.so.12 │     │libhipblas.so.1│    │libaclblas.so.x  │  │  ┃
┃  │  │libcublas.so.13 │     │libhipblas.so.2│    │libaclblas.so.y  │  │  ┃
┃  │  └────────────────┘     └───────────────┘    └─────────────────┘  │  ┃
┃  └───────────────────────────────────────────────────────────────────┘  ┃
┃                                                                         ┃
┃                            version scripts                              ┃
┃  ┌───────────────────────────────────────────────────────────────────┐  ┃
┃  │  libcublas.so.12 {     libhipblas.so.1 {      libaclblas.so.x {   │  ┃
┃  │    global:               global:                global:           │  ┃
┃  │      cublasSgemm_v2;       hipblasSgemm;          aclblasGemm;    │  ┃
┃  │  }                     }                      }                   │  ┃
┃  └───────────────────────────────────────────────────────────────────┘  ┃
┃                                                                         ┃
┃                           API Adaptive Layer                            ┃
┃  ┌───────────────────────────────────────────────────────────────────┐  ┃
┃  │cublasSgemm_v2() {      hipblasSgemm() {        aclblasGemm() {    │  ┃
┃  │  fakeSgemm();            fakeSgemm();            fakeSgemm();     │  ┃
┃  │}                       }                       }                  │  ┃
┃  └───────────────────────────────────────────────────────────────────┘  ┃
┃                                                                         ┃
┃                            Algorithm Layer                              ┃
┃  ┌───────────────────────────────────────────────────────────────────┐  ┃
┃  │                         fakeSgemm() {                             │  ┃
┃  │                           ...                                     │  ┃
┃  │                         }                                         │  ┃
┃  └───────────────────────────────────────────────────────────────────┘  ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

╔═══════════╗  ╔══════════╗  ╔════════════╗ ╔══════════╗  ╔═══════════════╗
║Nvidia GPU ║  ║ AMD GPU  ║  ║ Ascend NPU ║ ║   CPU    ║  ║Other hardware ║
╚═══════════╝  ╚══════════╝  ╚════════════╝ ╚══════════╝  ╚═══════════════╝
```


# Support List

# CUDA

- libcuda.so.1
- libcudart.so.12
- libcudart.so.13
- libcublas.so.12
- libcublas.so.13
- libcublasLt.so.12
- libcublasLt.so.13
- libcufft.so.11
- libcufft.so.12
- libcurand.so.10
- libcusparse.so.12

## ROCm

- libamdhip64.so.5
- libamdhip64.so.6
- libhipfft.so.0
- librocfft.so.0
- libhipsparse.so.1
- librocsparse.so.1
- libhiprand.so.1
- libhipblas.so.2
- libhipblaslt.so.0

## HPCC

- libhccompiler.so
- libhccl.so
- libhcruntime.so
- libhcblas.so
- libhcblasLt.so
- libhcfft.so
- libhcrand.so
- libhcsparse.so


# ENVs

## FAKECUDA_DEBUG

Enable fakeCUDA debug mode, this mode will enable fakeCUDA console log.

```bash
$ FAKECUDA_DEBUG=1 ./fakeCUDA.sh sparse
```

## FAKECUDA_DUMP

Enable fakeCUDA dump mode. This mode will dump some memory to files.

```bash
$ FAKECUDA_DUMP=1 ./fakeCUDA.sh sparse
```

# Example

## CUDA

```c
#include <stdio.h>
#include <curand.h>


int main(int argc, char *argv[])
{
	int version;
	curandGetVersion(&version);
	printf("curand version %d\n", version);
	return 0;
}
```

```
$ nvcc rand.cu -lcurand -o rand
```

```
$ ./rand
curand version 10400
$ ./fakeCUDA.sh ./rand
curand version 10
```

# TODO

It's a pity that **private kernel functions are not supported**. Perhaps in the future, this can be achieved through instruction set translation, similar to the GCN instruction set of AMD GPUs.
