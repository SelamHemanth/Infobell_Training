//show_monolithic: enhance the earlier “Hello, world” kernel module to print the process context (just show the process name and PID for now) that the init and cleanup code runs in.


#include <linux/init.h>
#include <linux/module.h>


MODULE_LICENSE("Dual BSD/GPL");

static int __init hello_init(void)
{
	pr_alert("Hemanth Warning\n");
	pr_emerg("Hemanth Emergency\n");
	pr_crit("Hemanth Critical\n");
	pr_err("Hemanth Error\n");
	pr_warn("Hemanth Warning\n");
	pr_notice("Hemanth Notice\n");
	pr_info("Hemanth Info\n");
	pr_devel("Hemanth Debug\n");
	return 0; /* success */
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

