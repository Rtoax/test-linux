Instruction and Registers Reference
===================================

# Register

## x86

Register Letters for the Intel x86 Architecture
Register Letter Registers That GCC May Use
	R General register (EAX, EBX, ECX, EDX, ESI, EDI, EBP, ESP)
	q General register for data (EAX, EBX, ECX, EDX)
	f Floating-point register
	t Top floating-point register
	u Second-from-top floating-point register
	a EAX register
	b EBX register
	c ECX register
	d EDX register
	x SSE register (Streaming SIMD Extension register)
	y MMX multimedia registers
	A An 8-byte value formed from EAX and EDX
	D Destination pointer for string operations (EDI)
	S Source pointer for string operations (ESI)


# SIMD

## x86

```
Bits: SSE < SSE2 < SSE3 < SSE4 < (SSE5) < AVX < AVX512
```

> SSE5: AMD发布，Intel生气不玩了


### Registers

```
                                                64bit  0
                                                +-------+
                                                |       |   MMX
                                                +-------+
                                                MM0 - MM7
                                         128bit         0
                                         +---------------+
                                         |               |  SSE
                                         +---------------+
                                             XMM0 - XMM7
                            256bit                      0
                           +-----------------------------+
                           |                             |  AVX
                           +-----------------------------+
                                   YMM0 - YMM15
512bit                                                  0
+--------------------------------------------------------+
|                                                        |  AVX-512
+--------------------------------------------------------+
                    ZMM0 - ZMM31
```

### MMX

Introduced on January 8, 1997 with its Pentium P5.

### SSE

#### SSE Instruction Set

- SSE: Added with Pentium III (70 new instructions)
- SSE2: Added with Pentium 4 in 2000 (144 new instructions over SSE)
- SSE3: Added with later Pentium 4 in 2004 (13 new instructions over SSE2)
- SSSE3: Added with Xeon 5100 and early Core 2 in 2006 (contains 16 new discrete instructions)
- SSE4: 2006 (consists of 54 instructions)
  - SSE4.1: Added with later Core 2 (Intel: consists of 47 instructions)
  - SSE4a: Added with Phenom (AMD: 4 SSE4 instructions and 4 new SSE instructions)
  - SSE4.2: Added with Nehalem (Intel: consists of the 7 remaining instructions)


### AVX, AVX2, AVX-512

- AVX:
- AVX2:
- AVX512:


## ARM

```
Bits: NEON < SVE <= SVE2
```

### NEON

- Since Armv7-A.
- Arm **Cortex-A** and Arm **Cortex-R** series of processors.

#### Operations

Neon instructions allow up to:

- 16x8-bit, 8x16-bit, 4x32-bit, 2x64-bit integer operations
- 8x16-bit, 4x32-bit, 2x64-bit floating-point operations


#### Register

```
128bit         0
+---------------+
|               |  NEON
+---------------+
    Q0-Q15


      32bit    0
       +--------+
       |        |
       +--------+
        D0-D31
```


### SVE/SVE2

- SVE/SVE2  Scalable Vector Registers

```
              128 bits ~ 2048 bits
                                  Neon
        LEN x 128                128 bits
+------------------------   --+------------+
|          Z32          ....  |    V32     |
+------------------------   --+------------+
                        ....      .....
+------------------------   --+------------+
|          Z2           ....  |    V2      |
+------------------------   ---------------+
|          Z1           ....  |    V1      |
+------------------------   --+------------+
```

- SVE/SVE2 Scalable Predicate Registers

```
   LEN x 16
+-----------+   +-----------+
|    P7     |   |    P15    |
+-----------+   +-----------+
     ...             ...
+-----------+   +-----------+
|    P1     |   |    p9     |
+-----------+   +-----------+   +----------+
|    P0     |   |    P8     |   |   FFR    |
+-----------+   +-----------+   +----------+
```

- SVE/SVE2 Scalable Vector Control Registers

```
  LEN=1...16
+----------+  +----------+  +----------+
| ZCR_EL1  |  | ZCR_EL2  |  | ZCR_EL3  |
+----------+  +----------+  +----------+
```


# Links

- https://www.felixcloutier.com/x86/
- [Intel ISA-L](https://github.com/intel/isa-l)
- https://en.wikipedia.org/wiki/CPUID
- https://en.wikipedia.org/wiki/Advanced_Vector_Extensions
- SSE: [https://en.wikibooks.org/wiki/X86_Assembly/SSE](https://en.wikibooks.org/wiki/X86_Assembly/SSE)
- AVX: [oracle](https://docs.oracle.com/cd/E36784_01/html/E36859/gntbd.html)
- AVX2: [oracle](https://docs.oracle.com/cd/E36784_01/html/E36859/gntae.html)
- AVX512: [oracle](https://docs.oracle.com/cd/E37838_01/html/E61064/gsesq.html)

