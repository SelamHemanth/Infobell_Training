#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual MIT/GPL");

static int __init hello_init(void)
{
		pr_debug("Hello  world\n");
#if 1
	int i;
	for(i=0;i<100;i++) {
		pr_debug("Hello  world\n");
		pr_debug_ratelimited("ratelimited: hello world\n");
	}
#endif
	return 0;
}

static void __exit hello_exit(void)
{
	pr_alert("Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
