/**
 *	File ./walk_page_table.c 
 *	Author Rong Tao
 *	Time 2021.11.10
 *
 *	Reference
 *	https://stackoverflow.com/questions/8980193/walking-page-tables-of-a-process-in-linux
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/pagewalk.h>
#include <linux/pgtable.h>
#include <linux/mm.h>

static int __attribute__((__unused__)) i;

static struct page *walk_page_table(unsigned long addr)
{
    pgd_t *pgd;
    pte_t *ptep, pte;
	p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;

    struct page *page = NULL;

    struct mm_struct *mm = current->mm;

    pgd = pgd_offset(mm, addr);
    if (pgd_none(*pgd) || pgd_bad(*pgd))
        goto out;
    printk(KERN_NOTICE "Valid pgd");

	p4d = p4d_offset(pgd, addr);
	if (p4d_none(*p4d) || p4d_bad(*p4d))
		goto out;
	printk(KERN_NOTICE "Valid p4d");

    pud = pud_offset(p4d, addr);
    if (pud_none(*pud) || pud_bad(*pud))
        goto out;
    printk(KERN_NOTICE "Valid pud");

    pmd = pmd_offset(pud, addr);
    if (pmd_none(*pmd) || pmd_bad(*pmd))
        goto out;
    printk(KERN_NOTICE "Valid pmd");

    ptep = pte_offset_map(pmd, addr);
    if (!ptep)
        goto out;
    pte = *ptep;

	page = pte_page(pte);
    if (page)
        printk(KERN_INFO "page frame struct is @ %p", page);

	pte_unmap(ptep);

 out:
    return page;
}

static int __init pagewalktest_init(void)
{
	struct page *find_page;
	
	printk("pagewalktest_init.\n");

	find_page = walk_page_table((unsigned long)&i);

	return 0;
}

static void __exit pagewalktest_exit(void)
{
	printk("pagewalktest_exit.\n");
}

module_init(pagewalktest_init);
module_exit(pagewalktest_exit);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
