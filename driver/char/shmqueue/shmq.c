/*****************************************************************************
 ** Share Memory Queue Driver
 ** Copyright(C) Rong Tao
 **
 ** History:
 ** 2019.09.30  Rong Tao	Create
 ** 2019.10.08  Rong Tao	Read Write lock
 *****************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/syscalls.h>
#include <linux/signal.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/rwlock.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <linux/kthread.h>
#include <asm/uaccess.h>

#include <linux/acpi.h>

#include "shmq.h"

#ifndef __KERNEL__
#error This file is Linux Kernel Device Driver Code File.
#endif

#if !defined(SHMQ_MAJOR) || !defined(SHMQ_DEV_NAME)
#error Must define SHMQ_MAJOR(maybe 123) and SHMQ_DEV_NAME(maybe "shmqueue")
#endif

#define __SHMQ_MAJOR		SHMQ_MAJOR
#define __SHMQ_DEV_NAME		SHMQ_DEV_NAME

#define __SHMQ_RWLOCK	   0

typedef struct shmq_dev_s {
#if !__SHMQ_RWLOCK
	struct mutex mxlock;
#else
	rwlock_t rwlock;
#endif
	dev_t dev_no;
	struct class *class;
	struct device *device;
	struct cdev cdev;
	wait_queue_head_t queue;
	atomic_t qwake;
	struct task_struct *thread;

	unsigned char *testmap;
	unsigned char *kmalloc_area;
} shmq_dev_t;

typedef enum {
	SHMQ_DEBUG,
	SHMQ_INFO,
	SHMQ_DEFAULT,
	SHMQ_NOTICE,
	SHMQ_EMERG,
	SHMQ_ALERT,
	SHMQ_WARNING,
	SHMQ_ERR,  
} shmq_log_lv;

static struct {
	int level;
	char *str;
} shmq_log_prefix[] __attribute__((unused)) = {
	{SHMQ_DEBUG,	KERN_DEBUG},
	{SHMQ_INFO,	 KERN_INFO},
	{SHMQ_DEFAULT,  KERN_DEFAULT},
	{SHMQ_NOTICE,   KERN_NOTICE},
	{SHMQ_EMERG,	KERN_EMERG},
	{SHMQ_ALERT,	KERN_ALERT},
	{SHMQ_WARNING,  KERN_WARNING},
	{SHMQ_ERR,	  KERN_ERR},
};

static inline int __attribute__((unused))
__shmq_log(shmq_log_lv level, const char *func, int line, const char *fmt, ...)
{
	int n=0;
#define SHMQ_LOG_PREFIX_FMT "[SHMQ %s | %s:%d] "
	va_list va;
	va_start(va, fmt);
	n = printk(SHMQ_LOG_PREFIX_FMT, shmq_log_prefix[level].str, func, line);
	n += vprintk(fmt, va);
	va_end(va);

	return n;
}

#define shmq_debug(fmt...)	  __shmq_log(SHMQ_DEBUG, __func__, __LINE__, fmt)
#define shmq_info(fmt...)	   __shmq_log(SHMQ_INFO, __func__, __LINE__, fmt)
#define shmq_default(fmt...)	__shmq_log(SHMQ_DEFAULT, __func__, __LINE__, fmt)
#define shmq_notice(fmt...)	 __shmq_log(SHMQ_NOTICE, __func__, __LINE__, fmt)
#define shmq_emerg(fmt...)	  __shmq_log(SHMQ_EMERG, __func__, __LINE__, fmt)
#define shmq_alert(fmt...)	  __shmq_log(SHMQ_ALERT, __func__, __LINE__, fmt)
#define shmq_warning(fmt...)	__shmq_log(SHMQ_WARNING, __func__, __LINE__, fmt)
#define shmq_err(fmt...)		__shmq_log(SHMQ_ERR, __func__, __LINE__, fmt)

static shmq_dev_t* shmq_dev[1];
static int __attribute__((unused)) _shmq_opened = 0;
static int __attribute__((unused)) _shmq_writeable = 1;
static int __attribute__((unused)) _shmq_readable = 1;

#define __SHMQ_IOC_WAIT	   SHMQ_IOC_WAIT
#define __SHMQ_IOC_WAKE_UP	SHMQ_IOC_WAKE_UP

static int shmq_open(struct inode *inode, struct file *file)
{
	shmq_debug(__SHMQ_DEV_NAME"\n");
	shmq_info("inode->i_nlink = %d\n", inode->i_nlink);
	shmq_info("inode->i_count = %d\n", inode->i_count);

	return 0;
}

static int condition = 0; 
static ssize_t shmq_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	shmq_debug(__SHMQ_DEV_NAME"\n");
	
#if __SHMQ_RWLOCK	
	write_lock(&shmq_dev[0]->rwlock);
#else 
	mutex_lock(&shmq_dev[0]->mxlock);
#endif

	/* copy from user space */
	if (copy_from_user(shmq_dev[0]->testmap, buf, count)) {
		shmq_err("write error!\n");
	}
	
#if __SHMQ_RWLOCK	
	write_unlock(&shmq_dev[0]->rwlock);
#else 
	mutex_unlock(&shmq_dev[0]->mxlock);
#endif

	condition = 1;
	wake_up_interruptible(&shmq_dev[0]->queue);
	
	return count;
}

static ssize_t shmq_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	shmq_debug(__SHMQ_DEV_NAME"\n");

	if (!condition)	//条件可以在中断处理函数或另外的接口中置位
		wait_event_interruptible((shmq_dev[0]->queue), condition);
	
#if __SHMQ_RWLOCK  
	read_lock(&shmq_dev[0]->rwlock);
#else 
	mutex_lock(&shmq_dev[0]->mxlock);
#endif

	if (copy_to_user(buf, shmq_dev[0]->testmap, count)) {
		shmq_err("read error!\n");
	}

	condition = 0;
	
#if __SHMQ_RWLOCK  
	read_unlock(&shmq_dev[0]->rwlock);
#else 
	mutex_unlock(&shmq_dev[0]->mxlock);
#endif

	return count;
}

static int shmq_flush(struct file *file, fl_owner_t id)
{
	shmq_debug(__SHMQ_DEV_NAME"\n");
	return 0;
}

static int shmq_fsync(struct file *file, loff_t off1, loff_t off2, int datasync)
{
	shmq_debug(__SHMQ_DEV_NAME"\n");
	return 0;
}

static int shmq_fasync(int i1, struct file *file, int i2)
{
	shmq_debug(__SHMQ_DEV_NAME"\n");
	return 0;
}

static int shmq_flock(struct file *file, int operation, struct file_lock *file_lock)
{
	shmq_debug(__SHMQ_DEV_NAME"\n");
	return 0;
}

static unsigned int shmq_poll(struct file *file, struct poll_table_struct *tab)
{
	shmq_debug(__SHMQ_DEV_NAME"\n");
	return 0;
}

static long shmq_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int result;
	
	shmq_debug(__SHMQ_DEV_NAME"\n");
	
	switch (cmd) {	
	case __SHMQ_IOC_WAIT:
		result=10;
		break;
	case __SHMQ_IOC_WAKE_UP:
		result=20;
		break;
	default:
		return -ENOTTY;			
	}
	
	return(result);
}

static int shmq_mmap(struct file *file, struct vm_area_struct *vma)
{
	int ret;
	shmq_debug(__SHMQ_DEV_NAME"\n");
	ret = remap_pfn_range(vma,vma->vm_start,
		       virt_to_phys((void *)((unsigned long)shmq_dev[0]->kmalloc_area))>>PAGE_SHIFT,
		       vma->vm_end-vma->vm_start,
		       PAGE_SHARED);
	if (ret != 0) {
		shmq_warning("remap_pfn_range error.\n");
		return -EAGAIN;
	} 
	return ret;
}

static int shmq_release(struct inode *node, struct file *file)
{
	shmq_debug(__SHMQ_DEV_NAME"\n");
	return 0;
}

static struct file_operations shmq_flops = {
	.owner = THIS_MODULE,
	.open = shmq_open,
	.write = shmq_write,
	.read = shmq_read,
	.flush = shmq_flush,
	.fsync = shmq_fsync,
	.fasync = shmq_fasync,
	.flock = shmq_flock,
	.poll = shmq_poll,
	.unlocked_ioctl = shmq_ioctl,
	.compat_ioctl = shmq_ioctl,
	.mmap = shmq_mmap,
	.release = shmq_release,
	
};

static int __init shmq_init(void)
{
	int ret;
	unsigned char *virt_addr;
	
	/* init shmq_dev */
	memset(&shmq_dev[0], 0, sizeof(shmq_dev_t*) * sizeof(shmq_dev)/sizeof(shmq_dev_t*));
	shmq_dev[0]  = (shmq_dev_t*)kzalloc(sizeof(shmq_dev_t), GFP_KERNEL);
	
	shmq_dev[0]->dev_no = MKDEV(__SHMQ_MAJOR , 0);
	   
	ret = register_chrdev_region(shmq_dev[0]->dev_no , 1 ,__SHMQ_DEV_NAME);
	if (ret < 0) {
		shmq_warning(__SHMQ_DEV_NAME " can't register major number.\n");
		goto err0;
	}
	
	cdev_init(&shmq_dev[0]->cdev , &shmq_flops) ;
	shmq_dev[0]->cdev.owner = THIS_MODULE ;
	shmq_dev[0]->cdev.ops = &shmq_flops ;
	
	shmq_debug(__SHMQ_DEV_NAME " Initialized.\n");
	
	ret = cdev_add(&shmq_dev[0]->cdev , shmq_dev[0]->dev_no , 1) ;
	if (ret < 0) {
		shmq_debug(__SHMQ_DEV_NAME "cdev add error !\n") ;
		ret = -1;
		goto err2;
	}
	
#if 0
	shmq_dev[0]->class = class_create(THIS_MODULE, __SHMQ_DEV_NAME);
	if (IS_ERR((void *)shmq_dev[0]->class)) {
		shmq_err("failed create class");
		shmq_dev[0]->class = NULL;
	}
#endif

	if (shmq_dev[0]->class) {
		shmq_dev[0]->device = device_create(shmq_dev[0]->class, NULL, shmq_dev[0]->dev_no, NULL, __SHMQ_DEV_NAME);
		if (IS_ERR((void *)shmq_dev[0]->device)) {
			shmq_err("failed create / device\n");
			ret = -2;
			goto err2;
		}
		dev_info(shmq_dev[0]->device, "Device: %s\n", __SHMQ_DEV_NAME);
	}

#if __SHMQ_RWLOCK  
	rwlock_init(&shmq_dev[0]->rwlock); //read write lock is better
#else	
	mutex_init(&shmq_dev[0]->mxlock);
#endif
	
	/* TEST */
	shmq_dev[0]->testmap = kmalloc(4096,GFP_KERNEL);
	shmq_dev[0]->kmalloc_area=(unsigned char *)(((unsigned long)shmq_dev[0]->testmap +PAGE_SIZE-1)&PAGE_MASK);
	if (shmq_dev[0]->testmap == NULL) {
		shmq_err("Kernel mem get pages error\n");
	} 
	
	for (virt_addr = (unsigned char *)shmq_dev[0]->kmalloc_area;
		virt_addr<(unsigned char *)shmq_dev[0]->kmalloc_area+4096;
		virt_addr+=PAGE_SIZE) {
		SetPageReserved(virt_to_page(virt_addr)); 
	}
	memset(shmq_dev[0]->testmap, 0, 100); 
	shmq_debug("Test drv reg success !\n") ;

	init_waitqueue_head(&shmq_dev[0]->queue);
	
	return 0;
	
err2:
#if 0
	device_destroy(shmq_dev[0]->class, shmq_dev[0]->dev_no);
	class_destroy(shmq_dev[0]->class);
#endif
	cdev_del(&shmq_dev[0]->cdev);

	unregister_chrdev_region(shmq_dev[0]->dev_no, 1);
	
err0:
	kfree(shmq_dev[0]);
	shmq_dev[0] = NULL;
	shmq_err("init failed");
	
	return -1;
}

static void __exit shmq_exit(void)
{
#if 1
	if (shmq_dev[0]) {
		if (shmq_dev[0]->class) {
			device_destroy(shmq_dev[0]->class, shmq_dev[0]->dev_no);
			class_destroy(shmq_dev[0]->class);
		}
		
		cdev_del(&shmq_dev[0]->cdev);

		unregister_chrdev_region(shmq_dev[0]->dev_no, 1);

		kfree(shmq_dev[0]);
		shmq_dev[0] = NULL;
	}
#else   
	cdev_del(&shmq_dev[0]->cdev) ;
	unregister_chrdev_region(shmq_dev[0]->dev_no , 1);
#endif
}

module_init(shmq_init);
module_exit(shmq_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");

