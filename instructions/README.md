arm, x86 and amd64 instruction reference
=========================================

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

## x86 Bits

```
SSE < SSE2 < SSE3 < SSE4 < (SSE5) < AVX < AVX512
```

> SSE5: AMD发布，Intel生气不玩了


### AVX -> AVX2

TODO

## arm Bits

```
NEON < SVE <= SVE2
```

### NEON SVE/SVE2

```
     SVE/SVE2  Scalable Vector Registers

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


     SVE/SVE2 Scalable Predicate Registers

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


  SVE/SVE2 Scalable Vector Control Registers

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

