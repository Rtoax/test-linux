subdir-y += gic
subdir-y += idt
subdir-y += ioapic
subdir-y += request_irq
subdir-y += softirq
subdir-y += tasklet
subdir-y += trace-irqoff
subdir-y += workqueue
subdir-y += Rescheduling-interrupts

target-${IS_X86_64} += cli
