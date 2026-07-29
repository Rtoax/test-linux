==========================
x86-specific Documentation
==========================


Register
--------

.. code-block:: text

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


.. toctree::
   :maxdepth: 1

   simd


Links
-----

- Intel ISA-L https://github.com/intel/isa-l
- https://en.wikipedia.org/wiki/CPUID
- https://www.felixcloutier.com/x86/
