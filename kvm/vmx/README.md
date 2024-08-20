VMX - Virtual Machine Extensions
================================

* Intel-VT(Virtual Technology): VMX

```
    VMM                      VM
             VM Entry
+----------+ --------> +--------------+
| VMX Root |           | VMX Non-Root |
+----------+ <-------- +--------------+
             VM Exit
```

# Instructions

1. VMLAUNCH
2. VMCALL
3. VMXON
4. VMXOFF
5. VMRESUME

Guest Software Instructions:

1. INVEPT
2. INVVPID


## 机器码

```
#define VMLAUNCH_OPCODE ".byte 0x0f,0x01,0xc2\n"
#define VMCALL_OPCODE ".byte 0x0f,0x01,0xc1\n"
#define VMXOFF_OPCODE ".byte 0x0f,0x01,0xc4\n"
#define VMXON_OPCODE ".byte 0xf3,0x0f,0xc7\n"
#define VMRESUME_OPCODE ".byte 0x0f,0x01,0xc3\n"

#define INVEPT_OPCODE ".byte 0x66,0x0f,0x38,0x80\n" /* m128,r64/32 */
#define INVVPID_OPCODE ".byte 0x66,0x0f,0x38,0x81\n" /* m128,r64/32 */
```

