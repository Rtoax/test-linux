Instruction Reference
=====================

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

### MMX

Introduced on January 8, 1997 with its Pentium P5.

#### MMX Registers

Eight 128-bit registers: MM0 - MM7

```
64bit            0
+-----------------+
|                 |  MMX
+-----------------+
    MM0 - MM7
```


### SSE

#### SSE Instruction Set

- SSE: Added with Pentium III
- SSE2: Added with Pentium 4 in 2000
- SSE3: Added with later Pentium 4
- SSSE3: Added with Xeon 5100 and early Core 2
- SSE4
  - SSE4.1: Added with later Core 2
  - SSE4a: Added with Phenom
  - SSE4.2: Added with Nehalem

#### SSE, SSE2 Registers

Eight 128-bit registers: XMM0 XMM1 XMM2 XMM3 XMM4 XMM5 XMM6 XMM7

```
128bit                            0
+----------------------------------+
|                                  |  SSE, SSE2
+----------------------------------+
             XMM0 - XMM7
```


### AVX -> AVX2

TODO


## ARM

```
Bits: NEON < SVE <= SVE2
```

### NEON SVE/SVE2

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

