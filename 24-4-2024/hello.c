#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/delay.h>

/*show_monolithic: enhance the earlier “Hello, world” kernel module to print the process context (just show the process name and PID for now) that the init and cleanup code runs in.
 */

MODULE_LICENSE("Dual BSD/GPL");

static int __init hello_init(void)
{
	printk(KERN_CRIT "******************** Inserting the Module **************\n");
	printk(KERN_INFO "Process name -> %s\nProcess ID  -> %d\n",current->comm,current->pid);
	ssleep(30);
	return 0; /* success */
}

static void __exit hello_exit(void)
{
	printk(KERN_CRIT "********************* Removing the Module **************\n");
	printk(KERN_INFO "Process name -> %s\nProcess ID  -> %d\n",current->comm,current->pid);
}

module_init(hello_init);
module_exit(hello_exit);

