#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
static int irq;
static char* devname;
module_param(irq,int,0644);
module_param(devname,charp,0644);//用户向内核传参数的函数

static struct tasklet_struct my_tasklet;
static void tasklet_handler(unsigned long data){
	printk(KERN_ALERT"tasklet_handler is running\n");
}

static irqreturn_t myirq_handler(int irq,void* dev)
{
	static int count=0;
	printk("key:%d..\n",count+1);
	printk("get irq %d \n",*((int *) dev));
	printk("ISR is leaving..\n");
	tasklet_schedule(&my_tasklet);//调度tasklet
	count++;
	return IRQ_HANDLED;
}
static int __init hello_init(void)
{
	int req_ret;
	printk("Module is working..\n");
	tasklet_init(&my_tasklet,tasklet_handler,0);//动态申请tasklet
	req_ret=request_irq(irq,myirq_handler,IRQF_SHARED,devname,&irq);//中断申请(共享)
	printk(KERN_ALERT "req_ret is %d\n",req_ret);
	if(req_ret!=0){
		printk("%s request IRQ:%d failed..\n",devname,irq);
		return -1;
	}
	else
		printk("%s request IRQ:%d success..\n",devname,irq);
	return 0;
}
static void __exit hello_exit(void)
{
	printk("Module is leaving..\n");
	free_irq(irq,&irq);
	printk("%s request IRQ:%d success\n",devname,irq);
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
