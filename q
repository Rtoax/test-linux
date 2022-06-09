[1mdiff --git a/kvm/interrupt/scripts/bpftrace/kvm_irq_map_gsi.bt b/kvm/interrupt/scripts/bpftrace/kvm_irq_map_gsi.bt[m
[1mindex bb95675..bdfe35d 100755[m
[1m--- a/kvm/interrupt/scripts/bpftrace/kvm_irq_map_gsi.bt[m
[1m+++ b/kvm/interrupt/scripts/bpftrace/kvm_irq_map_gsi.bt[m
[36m@@ -1,4 +1,11 @@[m
 #!/usr/bin/env bpftrace[m
[32m+[m[32m/**[m
[32m+[m[32m * File: kvm_irq_map_gsi.bt[m
[32m+[m[32m * Author: Rong Tao <rongtao@cestc.cn>[m
[32m+[m[32m * Date: 2022.01.07[m
[32m+[m[32m *[m
[32m+[m[32m * gsi: Global System Interrupt[m
[32m+[m[32m */[m
 [m
 BEGIN[m
 {[m
[1mdiff --git a/kvm/interrupt/scripts/bpftrace/kvm_set_irq.bt b/kvm/interrupt/scripts/bpftrace/kvm_set_irq.bt[m
[1mindex 1c450af..64bb2dd 100755[m
[1m--- a/kvm/interrupt/scripts/bpftrace/kvm_set_irq.bt[m
[1m+++ b/kvm/interrupt/scripts/bpftrace/kvm_set_irq.bt[m
[36m@@ -1,4 +1,16 @@[m
 #!/usr/bin/env bpftrace[m
[32m+[m[32m/**[m
[32m+[m[32m * File: kvm_set_irq.bt[m
[32m+[m[32m * Author: Rong Tao <rongtao@cestc.cn>[m
[32m+[m[32m * Date: 2022.01.07[m
[32m+[m[32m *[m
[32m+[m[32m * kvm_set_irq: Trigger interrupt[m
[32m+[m[32m *  Qemu has same name api[m
[32m+[m[32m *   int kvm_set_irq(KVMState *s, int irq, int level)[m
[32m+[m[32m *   {[m
[32m+[m[32m *     kvm_vm_ioctl(s, KVM_IRQ_LINE_STATUS, &event);[m
[32m+[m[32m *   }[m
[32m+[m[32m */[m
 [m
 BEGIN[m
 {[m
[36m@@ -7,8 +19,9 @@[m [mBEGIN[m
 [m
 kprobe:kvm_set_irq[m
 {[m
[31m-	printf("kstack %s\n", kstack);[m
[31m-	printf("ustack %s\n", ustack);[m
[32m+[m	[32m$nr = arg2;[m
[32m+[m	[32m@k[kstack] = count();[m
[32m+[m	[32m@n[$nr] = count();[m
 }[m
 [m
 END[m
