#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/debugfs.h>
#include <linux/sched/mm.h>
#include <linux/kexec.h>
#include <linux/mm.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Gryanko");
MODULE_DESCRIPTION("Shows pagetable for the process");
MODULE_VERSION("0.01");

/*
 * Mapping of Intel - Linux levels
 *
 * Level: L4          L3          L2        L1
 * Linux: PGD    -->  PDU    -->  PMD  -->  PTE
 * Intel: PML4E  -->  PDPTE  -->  PDE  -->  PTE
 *
 * Intel Vol. 3A 4-23
 *
 */

#define DEBUG_DIR "pagetable_dump"
#define MIN_PID 1000
#define MAX_PID_STR_LEN 13 // -2147483647 max string len is 11 plus '\n' symbol and '\0'
#define MAX_PT_ENTRIES 512

#define HUGE_2M_MASK 0xFFFFFFFE00000
#define HUGE_1G_MASK 0xFFFFFC0000000

#define ADDRESS_IDX_SHIFT 9
#define ADDRESS_OFFSET_SHIFT 12

#define L0_LINE        "|"
#define L1_LINE        "\\_____ "
#define L1_SPACE       "|       "
#define L1_SPACE_INNER "|           "
#define L2_LINE        "\\__________ "
#define L2_SPACE       "|           "
#define L2_SPACE_INNER "|               "
#define L3_LINE        "\\______________ "
#define L3_SPACE       "|                   "
#define L3_SPACE_INNER "|                       "
#define L4_LINE        "\\______________________ "
#define L4_SPACE       "|                       "
#define L4_SPACE_INNER "|                           "

#define STR_TRUE       "True"
#define STR_FALSE      "False"
#define STR_USER       "User"
#define STR_KERNEL     "Kernel"
#define STR_WRITE      "Write"
#define STR_READ       "Read"

static pid_t process_pid = 0;
static DEFINE_MUTEX(pagetable_lock);


struct raw_table {
    void* entry[MAX_PT_ENTRIES];
};

static ssize_t pid_read(struct file *filp, char *buf, size_t len, loff_t * offset) {
    char tmp[MAX_PID_STR_LEN];
    mutex_lock(&pagetable_lock);
    memset(&tmp, 0, MAX_PID_STR_LEN);
    sprintf(tmp, "%d\n", process_pid);
    mutex_unlock(&pagetable_lock);
    return simple_read_from_buffer(buf, len, offset, tmp, sizeof(tmp));
}

static ssize_t pid_write(struct file *filp, const char *buf, size_t len, loff_t * off) {
    // Read pid from userspace
    ssize_t ret = 0;
    mutex_lock(&pagetable_lock);
    ret = kstrtoint_from_user(buf, len, 0, &process_pid);
    if (ret) {
        ret = -EFAULT;
        goto err;
    }
    if (process_pid < 0) {
        ret = -EINVAL;
        goto err;
    }

    ret = len;
err:
    mutex_unlock(&pagetable_lock);
    return ret;
}

static struct file_operations pid_ops = {
    .owner = THIS_MODULE,
    .open = simple_open,
    .read = pid_read,
    .write = pid_write,
};


// code from fs/proc/task_mmu.c
// not visible function
static int is_stack(struct vm_area_struct *vma)
{
    /*
     * We make no effort to guess what a given thread considers to be
     * its "stack".  It's not even well-defined for programs written
     * languages like Go.
     */
    return vma->vm_start <= vma->vm_mm->start_stack &&
    	vma->vm_end >= vma->vm_mm->start_stack;
}

static void dump_vmarea(struct seq_file *m, struct mm_struct *mm_pt, u64 idx) {
    struct vm_area_struct *vma = find_vma(mm_pt, idx);
    
    struct mm_struct *mm = vma->vm_mm;
    struct file *file = vma->vm_file;
    unsigned long ino = 0;
    unsigned long long pgoff = 0;
    unsigned long start, end;
    dev_t dev = 0;
    const char *name = NULL;

    if (vma == NULL) {
        return;
    }
    seq_printf(m, "%s Page vm_area struct info: ", L4_SPACE);

    // code from fs/proc/task_mmu.c with custom formatting
    if (file) {
    	struct inode *inode = file_inode(vma->vm_file);
    	dev = inode->i_sb->s_dev;
    	ino = inode->i_ino;
    	pgoff = ((loff_t)vma->vm_pgoff) << PAGE_SHIFT;
    }

    start = vma->vm_start;
    end = vma->vm_end;

    /*
     * Print the dentry name for named mappings, and a
     * special [heap] marker for the heap:
     */
    if (file) {
    	seq_pad(m, ' ');
    	seq_file_path(m, file, "\n");
    	goto done;
    }

    if (vma->vm_ops && vma->vm_ops->name) {
    	name = vma->vm_ops->name(vma);
    	if (name)
    		goto done;
    }
#if 0
    if (vma->vm_flags & VM_MPX)
    	name = "[mpx]";
#endif
    if (!name) {
    	if (!mm) {
    		name = "[vdso]";
    		goto done;
    	}

    	if (vma->vm_start <= mm->brk &&
    	    vma->vm_end >= mm->start_brk) {
    		name = "[heap]";
    		goto done;
    	}

    	if (is_stack(vma))
    		name = "[stack]";
    }

done:
    if (name) {
    	seq_pad(m, ' ');
    	seq_puts(m, name);
    }
    seq_putc(m, '\n');
}

static void dump_pte(struct seq_file *m, struct mm_struct *mm_pt, u64 idx, u64 mask, void *table) {
    /* PTE entry
     * Intel Vol. 3A 4-27
     * Bit Position(s) Contents
     * 0 (P)           Present; must be 1 to map a 4-KByte page
     * 1 (R/W)         Read/write; if 0, writes may not be allowed to the 4-KByte page referenced by this entry (see Section 4.6)
     * 2 (U/S)         User/supervisor; if 0, user-mode accesses are not allowed to the 4-KByte page referenced by this entry (see Section 4.6)
     * 3 (PWT)         Page-level write-through; indirectly determines the memory type used to access the 4-KByte page referenced by this entry (see Section 4.9.2)
     * 4 (PCD)         Page-level cache disable; indirectly determines the memory type used to access the 4-KByte page referenced by this entry (see Section 4.9.2)
     * 5 (A)           Accessed; indicates whether software has accessed the 4-KByte page referenced by this entry (see Section 4.8)
     * 6 (D)           Dirty; indicates whether software has written to the 4-KByte page referenced by this entry (see Section 4.8)
     * 7 (PAT)         Indirectly determines the memory type used to access the 4-KByte page referenced by this entry (see Section 4.9.2)
     * 8 (G)           Global; if CR4.PGE = 1, determines whether the translation is global (see Section 4.10); ignored otherwise
     * 11:9            Ignored
     * (M–1):12        Physical address of the 4-KByte page referenced by this entry
     * 51:M            Reserved (must be 0)
     * 58:52           Ignored
     * 62:59           Protection key; if CR4.PKE = 1, determines the protection key of the page (see Section 4.6.2); ignored otherwise
     * 63 (XD)         If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 4-KByte page controlled by this entry; see Section 4.6); otherwise, reserved (must be 0)
     *
     * Physical address mask calculation for normal table:
     *  >>> bin(((1 << (51 - 12 + 1)) - 1) << 12)
     *  '0b1111111111111111111111111111111111111111000000000000'
     *  >>> hex(((1 << (51 - 12 + 1)) - 1) << 12)
     *  '0xffffffffff000'
     *
     * This is real address of Page Frame in physical memory
     */

    u64 entry = (u64)table;
    u64 phys = 0;
    u64 virt = 0;

    // Shift just for proper address display and vmarea search
    idx <<= ADDRESS_OFFSET_SHIFT;

    if(!(entry & _PAGE_PRESENT)) {
        seq_printf(m, "%s PTE is not present\n", L4_SPACE);
        return;
    }

    seq_printf(m, "%s Page attrs:\n"
            "%s PAGE RW:       %s\n"
            "%s PAGE USER:     %s\n"
            "%s PAGE PWT:      %s\n"
            "%s PAGE PCD:      %s\n"
            "%s PAGE ACCESSED: %s\n"
            "%s PAGE NX:       %s\n"
            "%s PAGE DIRTY:    %s\n"
            "%s PAGE PAT:      %s\n"
            "%s PAGE GLOBAL:   %s\n",
                L4_SPACE,
                L4_SPACE_INNER,
                entry & _PAGE_RW ? STR_WRITE : STR_READ,
                L4_SPACE_INNER,
                entry & _PAGE_USER ? STR_USER : STR_KERNEL,
                L4_SPACE_INNER,
                entry & _PAGE_PWT ? STR_TRUE : STR_FALSE,
                L4_SPACE_INNER,
                entry & _PAGE_PCD ? STR_TRUE : STR_FALSE,
                L4_SPACE_INNER,
                entry & _PAGE_ACCESSED ? STR_TRUE : STR_FALSE,
                L4_SPACE_INNER,
                entry & _PAGE_NX ? STR_TRUE : STR_FALSE,
                L4_SPACE_INNER,
                entry & _PAGE_DIRTY ? STR_TRUE : STR_FALSE,
                L4_SPACE_INNER,
                entry & _PAGE_PAT ? STR_TRUE : STR_FALSE,
                L4_SPACE_INNER,
                entry & _PAGE_GLOBAL ? STR_TRUE : STR_FALSE
            );
    phys = entry & mask;
    seq_printf(m, "%s Page physical address 0x%llx\n", L4_SPACE, phys);
    virt = (u64)phys_to_virt(phys);
    if(!virt_addr_valid(virt) || !IS_ALIGNED(phys, PAGE_SIZE)){
        seq_printf(m, "%s Page has incorrect virtual address\n", L4_SPACE);
        return;
    }
    seq_printf(m, "%s Page kernel virtual address 0x%llx\n", L4_SPACE, virt);
    if (entry & _PAGE_USER) {
        seq_printf(m, "%s Page user virtual address 0x%llx\n", L4_SPACE, idx);
        dump_vmarea(m, mm_pt, idx); 
    }

}

static void dump_pmd(struct seq_file *m, struct mm_struct *mm_pt, u64 idx, void *table) {
    /* PMD(PDe)
     * Intel 4-26 Vol. 3A
     *
     * Table with pointer to normal(4096) PMD(PDe) entries:
     * Bit Position(s) Contents
     * 0 (P)           Present; must be 1 to reference a page table
     * 1 (R/W)         Read/write; if 0, writes may not be allowed to the 2-MByte region controlled by this entry (see Section 4.6)
     * 2 (U/S)         User/supervisor; if 0, user-mode accesses are not allowed to the 2-MByte region controlled by this entry (see Section 4.6)
     * 3 (PWT)         Page-level write-through; indirectly determines the memory type used to access the page table referenced by this entry (see Section 4.9.2)
     * 4 (PCD)         Page-level cache disable; indirectly determines the memory type used to access the page table referenced by this entry (see Section 4.9.2)
     * 5 (A)           Accessed; indicates whether this entry has been used for linear-address translation (see Section 4.8)
     * 6               Ignored
     * 7 (PS)          Page size; must be 0 (otherwise, this entry maps a 2-MByte page; see Table 4-17)
     * 11:8            Ignored
     * (M–1):12        Physical address of 4-KByte aligned page table referenced by this entry
     * 51:M            Reserved (must be 0)
     * 62:52           Ignored
     * 63 (XD)         If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 2-MByte region controlled by this entry; see Section 4.6); otherwise, reserved (must be 0)
     *
     * Intel Vol. 3A 4-25
     * Table with pointer to 2MB HugePage(PMD/PDe entries) PTE:
     * Bit Position(s) Contents
     * 0 (P)           Present; must be 1 to map a 2-MByte page
     * 1 (R/W)         Read/write; if 0, writes may not be allowed to the 2-MByte page referenced by this entry (see Section 4.6)
     * 2 (U/S)         User/supervisor; if 0, user-mode accesses are not allowed to the 2-MByte page referenced by this entry (see Section 4.6)
     * 3 (PWT)         Page-level write-through; indirectly determines the memory type used to access the 2-MByte page referenced by this entry (see Section 4.9.2)
     * 4 (PCD)         Page-level cache disable; indirectly determines the memory type used to access the 2-MByte page referenced by this entry (see Section 4.9.2)
     * 5 (A)           Accessed; indicates whether software has accessed the 2-MByte page referenced by this entry (see Section 4.8)
     * 6 (D)           Dirty; indicates whether software has written to the 2-MByte page referenced by this entry (see Section 4.8)
     * 7 (PS)          Page size; must be 1 (otherwise, this entry references a page table; see Table 4-18)
     * 8 (G)           Global; if CR4.PGE = 1, determines whether the translation is global (see Section 4.10); ignored otherwise
     * 11:9            Ignored
     * 12 (PAT)        Indirectly determines the memory type used to access the 2-MByte page referenced by this entry (see Section 4.9.2)
     * 20:13           Reserved (must be 0)
     * (M–1):21        Physical address of the 2-MByte page referenced by this entry
     * 51:M            Reserved (must be 0)
     * 58:52           Ignored
     * 62:59           Protection key; if CR4.PKE = 1, determines the protection key of the page (see Section 4.6.2); ignored otherwise
     * 63 (XD)         If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 2-MByte page controlled by this entry; see Section 4.6); otherwise, reserved (must be 0)
     *
     * Physical address mask calculation for normal table:
     *  >>> bin(((1 << (51 - 12 + 1)) - 1) << 12)
     *  '0b1111111111111111111111111111111111111111000000000000'
     *  >>> hex(((1 << (51 - 12 + 1)) - 1) << 12)
     *  '0xffffffffff000'
     *
     * Physical address mask calculation for huge table:
     *   >>> bin(((1 << (51 - 21 + 1)) - 1) << 21)
     *   '0b1111111111111111111111111111111000000000000000000000'
     *   >>> hex(((1 << (51 - 21 + 1)) - 1) << 21)
     *   '0xfffffffe00000'
     * 
     *  For offset in 1GB Huge Page used 21 bits
     */
    struct raw_table *pte_tables = NULL;

    u64 entry = (u64)table;
    u64 pte_phys = 0;

    int pte_l1_i = 0;

    if(!(entry & _PAGE_PRESENT)) {
        seq_printf(m, "%s PMD is not present\n", L3_SPACE);
        return;
    }

    seq_printf(m, "%s PMD attrs:\n"
            "%s PAGE RW:       %s\n"
            "%s PAGE USER:     %s\n"
            "%s PAGE PWT:      %s\n"
            "%s PAGE PCD:      %s\n"
            "%s PAGE ACCESSED: %s\n"
            "%s PAGE NX:       %s\n"
            "%s PAGE PSE:      %s\n",
                L3_SPACE,
                L3_SPACE_INNER,
                entry & _PAGE_RW ? STR_WRITE : STR_READ,
                L3_SPACE_INNER,
                entry & _PAGE_USER ? STR_USER : STR_KERNEL,
                L3_SPACE_INNER,
                entry & _PAGE_PWT ? STR_TRUE : STR_FALSE,
                L3_SPACE_INNER,
                entry & _PAGE_PCD ? STR_TRUE : STR_FALSE,
                L3_SPACE_INNER,
                entry & _PAGE_ACCESSED ? STR_TRUE : STR_FALSE,
                L3_SPACE_INNER,
                entry & _PAGE_NX ? STR_TRUE : STR_FALSE,
                L3_SPACE_INNER,
                entry & _PAGE_PSE ? STR_TRUE : STR_FALSE // HugePages 2M
            );

    if (entry & _PAGE_PSE) {
        // user space address shifted for 21 bit because of direct mapping to PTE
        seq_printf(m, "%s PTE is 2MB HugePage\n", L3_SPACE);
        dump_pte(m, mm_pt, idx << (ADDRESS_IDX_SHIFT + ADDRESS_OFFSET_SHIFT), HUGE_2M_MASK, table);
        return;
    }

    pte_phys = entry & PHYSICAL_PAGE_MASK;
    seq_printf(m, "%s PTE entry physical address 0x%llx\n", L3_SPACE, pte_phys);
    pte_tables = phys_to_virt(pte_phys);
    if(!virt_addr_valid(pte_tables) || !IS_ALIGNED(pte_phys, PAGE_SIZE)){
        seq_printf(m, "%s PTE entry has incorrect virtual address\n", L3_SPACE);
        return;
    }
    seq_printf(m, "%s PTE entry virtual address 0x%llx\n", L3_SPACE, (u64)pte_tables);
    for (pte_l1_i = 0; pte_l1_i < MAX_PT_ENTRIES; ++pte_l1_i) {
        if (pte_tables->entry[pte_l1_i]) {
            seq_printf(m, "%s PTE idx %.3d persists in memory:\n", L4_LINE, pte_l1_i);
            dump_pte(m, mm_pt, pte_l1_i | (idx << ADDRESS_IDX_SHIFT), PHYSICAL_PAGE_MASK, pte_tables->entry[pte_l1_i]);
        }
    }
}

static void dump_pud(struct seq_file *m, struct mm_struct *mm_pt, u64 idx, void *table) {
    /* PUD(PDPTe)
     * Intel Vol. 3A 4-25
     *
     * Table with pointer to normal(4096) PMD(PDe) entries:
     * Bit Position(s) Contents
     * 0 (P)           Present; must be 1 to reference a page directory
     * 1 (R/W)         Read/write; if 0, writes may not be allowed to the 1-GByte region controlled by this entry (see Section 4.6)
     * 2 (U/S)         User/supervisor; if 0, user-mode accesses are not allowed to the 1-GByte region controlled by this entry (see Section 4.6)
     * 3 (PWT)         Page-level write-through; indirectly determines the memory type used to access the page directory referenced by this entry (see Section 4.9.2)
     * 4 (PCD)         Page-level cache disable; indirectly determines the memory type used to access the page directory referenced by this entry (see Section 4.9.2)
     * 5 (A)           Accessed; indicates whether this entry has been used for linear-address translation (see Section 4.8)
     * 6               Ignored
     * 7 (PS)          Page size; must be 0 (otherwise, this entry maps a 1-GByte page; see Table 4-15)
     * 11:8            Ignored
     * (M–1):12        Physical address of 4-KByte aligned page directory referenced by this entry
     * 51:M            Reserved (must be 0)
     * 62:52           Ignored
     * 63 (XD)         If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 1-GByte region controlled by this entry; see Section 4.6); otherwise, reserved (must be 0)
     *
     * Intel 4-24 Vol. 3A
     * Table with pointer to 1GB HugePage(no PUD/PDPTe, PMD/PDe entries) PTE:
     * Bit Position(s) Contents
     * 0 (P)           Present; must be 1 to map a 1-GByte page
     * 1 (R/W)         Read/write; if 0, writes may not be allowed to the 1-GByte page referenced by this entry (see Section 4.6)
     * 2 (U/S)         User/supervisor; if 0, user-mode accesses are not allowed to the 1-GByte page referenced by this entry (see Section 4.6)
     * 3 (PWT)         Page-level write-through; indirectly determines the memory type used to access the 1-GByte page referenced by this entry (see Section 4.9.2)
     * 4 (PCD)         Page-level cache disable; indirectly determines the memory type used to access the 1-GByte page referenced by this entry (see Section 4.9.2)
     * 5 (A)           Accessed; indicates whether software has accessed the 1-GByte page referenced by this entry (see Section 4.8)
     * 6 (D)           Dirty; indicates whether software has written to the 1-GByte page referenced by this entry (see Section 4.8)
     * 7 (PS)          Page size; must be 1 (otherwise, this entry references a page directory; see Table 4-16)
     * 8 (G)           Global; if CR4.PGE = 1, determines whether the translation is global (see Section 4.10); ignored otherwise
     * 11:9            Ignored
     * 12 (PAT)        Indirectly determines the memory type used to access the 1-GByte page referenced by this entry (see Section 4.9.2)1
     * 29:13           Reserved (must be 0)
     * (M–1):30        Physical address of the 1-GByte page referenced by this entry
     * 51:M            Reserved (must be 0)
     * 58:52           Ignored
     * 62:59           Protection key; if CR4.PKE = 1, determines the protection key of the page (see Section 4.6.2); ignored otherwise
     * 63 (XD)         If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 1-GByte page controlled by this entry; see Section 4.6); otherwise, reserved (must be 0)
     *
     * Physical address mask calculation for normal table:
     *  >>> bin(((1 << (51 - 12 + 1)) - 1) << 12)
     *  '0b1111111111111111111111111111111111111111000000000000'
     *  >>> hex(((1 << (51 - 12 + 1)) - 1) << 12)
     *  '0xffffffffff000'
     *
     * Physical address mask calculation for huge table:
     *  >>> bin(((1 << (51 - 30 + 1)) - 1) << 30)
     *  '0b1111111111111111111111000000000000000000000000000000'
     *  >>> hex(((1 << (51 - 30 + 1)) - 1) << 30)
     *  '0xfffffc0000000'
     * 
     *  For offset in 1GB Huge Page used 30 bits
     */
    struct raw_table *pmd_tables = NULL;

    u64 entry = (u64)table;
    u64 pmd_phys = 0;

    int pmd_l2_i = 0;

    if(!(entry & _PAGE_PRESENT)) {
        seq_printf(m, "%s PUD is not present\n", L2_SPACE);
        return;
    }

    seq_printf(m, "%s PUD attrs:\n"
            "%s PAGE RW:       %s\n"
            "%s PAGE USER:     %s\n"
            "%s PAGE PWT:      %s\n"
            "%s PAGE PCD:      %s\n"
            "%s PAGE ACCESSED: %s\n"
            "%s PAGE NX:       %s\n"
            "%s PAGE PSE:      %s\n",
                L2_SPACE,
                L2_SPACE_INNER,
                entry & _PAGE_RW ? STR_WRITE : STR_READ,
                L2_SPACE_INNER,
                entry & _PAGE_USER ? STR_USER : STR_KERNEL,
                L2_SPACE_INNER,
                entry & _PAGE_PWT ? STR_TRUE : STR_FALSE,
                L2_SPACE_INNER,
                entry & _PAGE_PCD ? STR_TRUE : STR_FALSE,
                L2_SPACE_INNER,
                entry & _PAGE_ACCESSED ? STR_TRUE : STR_FALSE,
                L2_SPACE_INNER,
                entry & _PAGE_NX ? STR_TRUE : STR_FALSE,
                L2_SPACE_INNER,
                entry & _PAGE_PSE ? STR_TRUE : STR_FALSE // HugePages 1G
            );

    // not tested
    if (entry & _PAGE_PSE) {
        seq_printf(m, "%s PTE is 1GB HugePage\n", L3_SPACE);
        // user space address shifted for 30 bit because of direct mapping to PTE
        dump_pte(m, mm_pt, idx << (2 * ADDRESS_IDX_SHIFT + ADDRESS_OFFSET_SHIFT), HUGE_1G_MASK, table);
        return;
    }

    pmd_phys = entry & PHYSICAL_PAGE_MASK;
    seq_printf(m, "%s PMD entry physical address 0x%llx\n", L2_SPACE, pmd_phys);
    pmd_tables = phys_to_virt(pmd_phys);
    if(!virt_addr_valid(pmd_tables) || !IS_ALIGNED(pmd_phys, PAGE_SIZE)){
        seq_printf(m, "%s PMD entry has incorrect virtual address\n", L2_SPACE);
        return;
    }
    seq_printf(m, "%s PMD entry virtual address 0x%llx 0x%llx\n", L2_SPACE, (u64)pmd_tables, idx);
    for (pmd_l2_i = 0; pmd_l2_i < MAX_PT_ENTRIES; ++pmd_l2_i) {
        if (pmd_tables->entry[pmd_l2_i]) {
            seq_printf(m, "%s PMD idx %.3d persists in memory:\n", L3_LINE, pmd_l2_i);
            dump_pmd(m, mm_pt, pmd_l2_i | (idx << ADDRESS_IDX_SHIFT), pmd_tables->entry[pmd_l2_i]);
        }
    }
   
}

static void dump_pgd(struct seq_file *m, struct mm_struct *mm_pt, u64 idx, void *table) {
    /* PGD(PML4E) entries
     * Intel Vol. 3A 4-23
     * Bit Position(s) Contents
     * 0 (P)           Present; must be 1 to reference a page-directory-pointer table
     * 1 (R/W)         Read/write; if 0, writes may not be allowed to the 512-GByte region controlled by this entry (see Section 4.6)
     * 2 (U/S)         User/supervisor; if 0, user-mode accesses are not allowed to the 512-GByte region controlled by this entry (see Section 4.6)
     * 3 (PWT)         Page-level write-through; indirectly determines the memory type used to access the page-directory-pointer table referenced by this entry (see Section 4.9.2)
     * 4 (PCD)         Page-level cache disable; indirectly determines the memory type used to access the page-directory-pointer table referenced by this entry (see Section 4.9.2)
     * 5 (A)           Accessed; indicates whether this entry has been used for linear-address translation (see Section 4.8)
     * 6               Ignored
     * 7 (PS)          Reserved (must be 0)
     * 11:8            Ignored
     * M–1:12          Physical address of 4-KByte aligned page-directory-pointer table referenced by this entry
     * 51:M            Reserved (must be 0)
     * 62:52           Ignored
     * 63 (XD)         If IA32_EFER.NXE = 1, execute-disable (if 1, instruction fetches are not allowed from the 512-GByte region controlled by this entry; see Section 4.6); otherwise, reserved (must be 0)
     * 
     * Physical address mask calculation:
     *  >>> bin(((1 << (51 - 12 + 1)) - 1) << 12)
     *  '0b1111111111111111111111111111111111111111000000000000'
     *  >>> hex(((1 << (51 - 12 + 1)) - 1) << 12)
     *  '0xffffffffff000'
     *
     * User space address:
     * R R R R R R R R R R R R R R R R | G G G G G G G G G | U U U U U U U U U | M M M M M M M M M | E E E E E E E E E | O O O O O O O O O O O O
     * 
     * Bit position(s) Contents
     * R               Reserved. Only 48 bits used for addressing 256GB of RAM
     * G               Page Global Directory index
     * U               Page Upper Directory index
     * M               Page Middle Directory index
     * E               Page Table Entry index
     * O               Offset inside physical page
     *
     */
    struct raw_table *pud_tables = NULL;

    u64 entry = (u64)table; // 4096 / 512 == 8 bytes or 64 bits per entry
    u64 pud_phys = 0;

    int pud_l3_i = 0;

    seq_printf(m, "%s PGD entry 0x%llx\n", L1_LINE, entry);
    if(!(entry & _PAGE_PRESENT)) {
        seq_printf(m, "%s PGD is not present\n", L1_SPACE);
        return;
    }
    seq_printf(m, "%s PGD attrs:\n"
            "%s PAGE RW:       %s\n"
            "%s PAGE USER:     %s\n"
            "%s PAGE PWT:      %s\n"
            "%s PAGE PCD:      %s\n"
            "%s PAGE ACCESSED: %s\n"
            "%s PAGE NX:       %s\n"
            "%s PAGE PSE:      %s\n",
                L1_SPACE,
                L1_SPACE_INNER,
                entry & _PAGE_RW ? STR_WRITE : STR_READ,
                L1_SPACE_INNER,
                entry & _PAGE_USER ? STR_USER : STR_KERNEL,
                L1_SPACE_INNER,
                entry & _PAGE_PWT ? STR_TRUE : STR_FALSE,
                L1_SPACE_INNER,
                entry & _PAGE_PCD ? STR_TRUE : STR_FALSE,
                L1_SPACE_INNER,
                entry & _PAGE_ACCESSED ? STR_TRUE : STR_FALSE,
                L1_SPACE_INNER,
                entry & _PAGE_NX ? STR_TRUE : STR_FALSE,
                L1_SPACE_INNER,
                entry & _PAGE_PSE ? STR_TRUE : STR_FALSE // not possible for PGD
            );

    pud_phys = entry & PHYSICAL_PAGE_MASK;
    seq_printf(m, "%s PUD entry physical address 0x%llx\n", L1_SPACE, pud_phys);
    // phys_to_virt works only with kmalloc and lowmem
    pud_tables = phys_to_virt(pud_phys);
    if(!virt_addr_valid(pud_tables) || !IS_ALIGNED(pud_phys, PAGE_SIZE)){
        seq_printf(m, "%s PUD entry has incorrect virtual address\n", L1_SPACE);
        return;
    }
    seq_printf(m, "%s PUD entry virtual address 0x%llx\n", L1_SPACE, (u64)pud_tables);
    for (pud_l3_i = 0; pud_l3_i < MAX_PT_ENTRIES; ++pud_l3_i) {
        if (pud_tables->entry[pud_l3_i]) {
            seq_printf(m, "%s PUD idx %.3d persists in memory:\n", L2_LINE, pud_l3_i);
            // second parameter calculates possible user space address
            // shifting by 9 because of this is directory 
            dump_pud(m, mm_pt, pud_l3_i | (idx << ADDRESS_IDX_SHIFT), pud_tables->entry[pud_l3_i]);
        }
    }
}

static int dump_show(struct seq_file *m, void *p) {
    struct pid *pid_pt = NULL;
    struct task_struct *task_pt = NULL;
    struct mm_struct *mm_pt = NULL;
    struct raw_table *pgd_l4 = NULL;

    phys_addr_t pgd_phys;

    int pgd_l4_i = 0;

    if (process_pid < MIN_PID) {
        seq_printf(m, "pid %d is less than %d\n", process_pid, MIN_PID);
        goto exit;
    }

    pid_pt = find_get_pid(process_pid);
    if (!pid_pt) {
        seq_printf(m, "pid %d is not found\n", process_pid);
        goto exit;
    }

    task_pt = pid_task(pid_pt, PIDTYPE_PID);
    if (!task_pt) {
        seq_printf(m, "task with pid %d is not found\n", process_pid);
        goto exit;
    }

    mm_pt = get_task_mm(task_pt);
    if (!mm_pt) {
        seq_printf(m, "mm with pid %d is not found\n", process_pid);
        goto exit;
    }

    if (!mm_pt->pgd) {
        seq_printf(m, "PGD with pid %d is not found\n", process_pid);
        goto exit;
    }

    pgd_phys = virt_to_phys(mm_pt->pgd);
    seq_printf(m, "%s PGD virtual address is 0x%llx\n", L0_LINE, (u64)mm_pt->pgd);
    seq_printf(m, "%s PGD physical address is 0x%llx\n", L0_LINE, (u64)pgd_phys);

    // starting iteration through top-level directory
    pgd_l4 = (struct raw_table*)mm_pt->pgd;
    for (pgd_l4_i = 0; pgd_l4_i < MAX_PT_ENTRIES; ++pgd_l4_i) {
        if (pgd_l4->entry[pgd_l4_i]) {
            seq_printf(m, "%s PGD idx %.3d persists in memory:\n", L0_LINE, pgd_l4_i);
            dump_pgd(m, mm_pt, pgd_l4_i, pgd_l4->entry[pgd_l4_i]);
        }
    }
exit:
    return 0;
}

static int dump_open(struct inode *inode, struct file *file) {
    return single_open(file, dump_show, inode->i_private);
}

static const struct file_operations dump_ops = {
    .owner        = THIS_MODULE,
    .open        = dump_open,
    .read        = seq_read,
    .llseek        = seq_lseek,
    .release    = single_release,
};

static struct dentry *pagetable_dir;

static int __init pagetable_init(void) {
    BUILD_BUG_ON(PAGE_SIZE != 4096);
    BUILD_BUG_ON(PTRS_PER_PGD != MAX_PT_ENTRIES);
    BUILD_BUG_ON(PTRS_PER_PUD != MAX_PT_ENTRIES);
    BUILD_BUG_ON(PTRS_PER_PMD != MAX_PT_ENTRIES);
    BUILD_BUG_ON(PTRS_PER_PTE != MAX_PT_ENTRIES);

    pagetable_dir = debugfs_create_dir(DEBUG_DIR, NULL);

    if (!pagetable_dir) {
        return -ENOMEM;
    }

    if (!debugfs_create_file("pid", 0600, pagetable_dir, NULL, &pid_ops)) {
        goto err;
    }
    if (!debugfs_create_file("dump", 0400, pagetable_dir, NULL, &dump_ops)) {
        goto err;
    }

    return 0;
err:
    debugfs_remove_recursive(pagetable_dir);
    return -ENOMEM;
}

static void __exit pagetable_exit(void) {
    mutex_unlock(&pagetable_lock);
    debugfs_remove_recursive(pagetable_dir);
}

module_init(pagetable_init);
module_exit(pagetable_exit);
