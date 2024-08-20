VMCS - Virtual Machine Control Structure
========================================

* One VMCS per VCPU;
* VMCS to VCPU ~= `task_struct` to task;
* VMCS == 4KB;


# Operate Instructions

1. vmclear
2. vmptrld
3. vmptrst
4. vmread
5. vmwrite

## 机器码

```
#define VMCLEAR_OPCODE ".byte 0x66,0x0f,0xc7\n" /* reg/opcode: /6 */
#define VMPTRLD_OPCODE ".byte 0x0f,0xc7\n" /* reg/opcode: /6 */
#define VMPTRST_OPCODE ".byte 0x0f,0xc7\n" /* reg/opcode: /7 */
#define VMREAD_OPCODE ".byte 0x0f,0x78\n"
#define VMWRITE_OPCODE ".byte 0x0f,0x79\n"
```


# struct vmcs

```c
struct vmcs {
	struct {
		u32 revision_id:31;
		u32 shadow_vmcs:1;
	} hdr;
	u32 abort;
	char data[];
};
```

* `revision_id`: Version of VMCS;
* `shadow_vmcs`:
* `abort`: When `VM Exit` ERROR, VMX-Abort happen, saved here;
* `data`: Read/Write by vmread/vmwrite, 6 regions:
	1. Guest-state Region;
	2. Host-state Region;
	3. VM-Execution Control Region;
	4. VM-Exit Control Region;
	5. VM-Entry Control Region;
	6. VM-Exit Information Region;

