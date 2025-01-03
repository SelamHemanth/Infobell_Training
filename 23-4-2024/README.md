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
 * We use `insmod` for insert the module into kernel and `rmmod` for remove the module.
 * `printk` is the API tool to print the string. Backend insmod and rmmod containd following system calls to enter into kernel layer.
 * `insmod`  -> init_module
 * `rmmod`   -> delete_moduel   
 * This is the sample syntax 
	`printk(KERN_ALERT "Hello, world\n");`
 * The printk format string includes a printk “logging level” directive; you should use one of:(from include/linux/kern_levels.h)
```javascript
#define KERN_SOH "\001"  		/* ASCII Start Of Header */
#define KERN_SOH_ASCII '\001'
#define KERN_EMERG KERN_SOH "0" 	/* system is unusable */
#define KERN_ALERT KERN_SOH "1" 	/* action must be taken immediately */
#define KERN_CRIT KERN_SOH "2" 		/* critical conditions */
#define KERN_ERR KERN_SOH "3" 		/* error conditions */
#define KERN_WARNING KERN_SOH "4" 	/* warning conditions */
#define KERN_NOTICE KERN_SOH "5"	/* normal but significant condition */
#define KERN_INFO KERN_SOH "6" 		/* informational */
#define KERN_DEBUG KERN_SOH "7" 	/* debug-level messages */
#define KERN_DEFAULT KERN_SOH "d" 	/* the default kernel loglevel */
```
 * It is possible to read and modify the console loglevel using the text file
	'/proc/sys/kernel/printk'
 * Writing a single value to this file changes the current loglevel to that value; thus, for example, you can cause all kernel messages to appear at the console by simply entering:
	' echo “8 4 1 7” > /proc/sys/kernel/printk '

 * This is sample code...

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
 * While booting machine we find some messages like,
	 
```javascript
	 ...
	 [ 2109.612806] ks3231 1-0068: IRQ! #5
	 ... 
```
 * These are comes with pr_fmt() and dev_fmt() macros.
	
  * `#define pr_fmt(fmt) "%s:%s(): " fmt, KBUILD_MODNAME, __func__`
  * Eg:
```javascript
[ 5980.719483] dht2x_kdrv:dht2x_read_sensors(): str_crc=4b
```
  * `#define dev_fmt(fmt) "%s(): " fmt, __func__`
  * Eg:
```javascript
[ 6225.672886] dht2x_kdrv:dht2x_read_sensors(): str_crc=32
[ 6225.672904] dht2x 1-0038: dht2x_read_sensors(): crc obtd=0x32 crc=0x32
[ 6225.672920] dht2x 1-0038: dht2x_temp_show(): Temperature=24826 milliC
```
 * Their is so many [print formats](https://www.kernel.org/doc/Documentation/printk-formats.txt) are available to print the different type of data in different format. 
 

---
 `Note:` **$ journalctl** -> It shows the all debug imformation of system.If you want to see current using `-b` option and `-f` for see live begug messages. 

***Compilation of Kernel Module***
---

 * Kernel compiler is also compiles like C programming. But, only differece is the output file is kernel object file (.ko).
 * These are the packages to install to compile the kernel module
```javascript
sudo apt-get install linux-headers-generic gcc
```
 * Simplest Makefile for a kernel module (LKM):
```javascript
$ cat Makefile
// Simplest LKM Makefile
obj-m = hello.o
KDIR:= /lib/modules/$(shell uname -r)/build
PWD:= $(shell pwd)
all:
make -C $(KDIR) M=$(PWD) modules
install:
make -C $(KDIR) M=$(PWD) modules_install
clean:
make -C $(KDIR) M=$(PWD) clean
```
 * Build with:
```javascript
$ make				//It builds the kernel object file
$ make modules_install		//It installs the module into kernel updates
```

