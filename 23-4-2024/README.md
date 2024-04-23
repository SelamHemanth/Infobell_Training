# Kernel Build
---

***Kenel Configuration***
---

 * init/Kconfig - defines the 'General Setup' menu items!. Write the below code in Kconfig file.

```javascript
 config HEMANTH
        bool "Hai Hemanth , This is your config button"
        default n
        help
        Turns on the hook that will cause this kernel to ...
        blah blah blah
```
**Note**: Make sure duplicate the backup file. 

***Kernel Testing***
---

 * **kbuild Test Robot**  -> It is a automatic test tool for kernel, It is developed by Intel. 
 * **lkp-tests**    -> It is a test hub. It contains several type of test cases.


***WRITING LOADABLE KERNEL MODULES***
---

 * Normally we write C codes are write in user mode i.e., **hello.c**. If you want to write C code in kernel mode, the file called as module. The module look like **hello.ko** . 
 * We use **insmod** for insert the module into kernel and **rmmod** for remove the module.
 * This is sampple code...

```javascript
#include <linux/init.h>
#include <linux/module.h>
/* From the official kernel doc:“Loadable kernel modules also require a MODULE_LICENSE() tag. This tag is neither a replacement for proper source code license information (SPDX-License-Identifier) nor in any way relevant for expressing or determining the exact license under which the source code of the module is provided. [...]”
*/
MODULE_LICENSE("Dual BSD/GPL");
static int __init hello_init(void)
{
printk(KERN_ALERT "Hello, world\n");
return 0; /* success */
}
static void __exit hello_exit(void)
{
printk(KERN_ALERT "Goodbye, cruel world\n");
}
module_init(hello_init);
module_exit(hello_exit);
```
