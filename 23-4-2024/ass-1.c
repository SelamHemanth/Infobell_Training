#include <linux/init.h>
#include <linux/module.h>

/* From the official kernel doc:“Loadable kernel modules also require a MODULE_LICENSE() tag. This tag is neither a replacement for proper source code license information (SPDX-License-Identifier) nor in any way relevant for expressing or determining the exact license under which the source code of the module is provided. [...]”
 */

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

