#include <stdio.h>
#include <linux/kvm.h>

int main()
{
	/**
	 * ./ioctl_values.out 2>/dev/null | awk '{print "@ioctls["$3"] = \""$1"\";"}'
	 *
	 * Output:
	 * @ioctls[0x000000004018ae40] = "KVM_SET_MEMORY_REGION";
	 */
#define P64(ioctl)	printf("%30s = 0x%016lx\n", #ioctl, ioctl)
#define P32(ioctl)	printf("%30s = %8s0x%08x\n", #ioctl, "", ioctl)
#ifdef KVM_SET_MEMORY_REGION
	P64(KVM_SET_MEMORY_REGION);
#endif
	P32(KVM_CREATE_VCPU);
	P64(KVM_GET_DIRTY_LOG);
#ifdef KVM_SET_MEMORY_ALIAS
	P64(KVM_SET_MEMORY_ALIAS);
#endif
	P32(KVM_SET_NR_MMU_PAGES);
	P32(KVM_GET_NR_MMU_PAGES);
	P64(KVM_SET_USER_MEMORY_REGION);
	P32(KVM_SET_TSS_ADDR);
	P64(KVM_SET_IDENTITY_MAP_ADDR);
	P32(KVM_CREATE_IRQCHIP);
	P64(KVM_IRQ_LINE);
	P64(KVM_GET_IRQCHIP);
	P64(KVM_SET_IRQCHIP);
	P32(KVM_CREATE_PIT);
	P64(KVM_GET_PIT);
	P64(KVM_SET_PIT);
	P64(KVM_IRQ_LINE_STATUS);
	P64(KVM_REGISTER_COALESCED_MMIO);
	P64(KVM_GET_XSAVE);
	P64(KVM_SET_XSAVE);
	P64(KVM_SIGNAL_MSI);
	P64(KVM_SET_XCRS);

	fprintf(stderr, "===== kvm_vcpu_ioctl =====\n");
	P32(KVM_RUN);
	P64(KVM_GET_REGS);
	P64(KVM_SET_REGS);
	P64(KVM_GET_SREGS);
	P64(KVM_SET_SREGS);
	P64(KVM_GET_MP_STATE);
	P64(KVM_SET_MP_STATE);
	P64(KVM_TRANSLATE);
	P64(KVM_SET_GUEST_DEBUG);
	P64(KVM_SET_SIGNAL_MASK);
	P64(KVM_GET_FPU);
	P64(KVM_SET_FPU);
	return 0;
}

