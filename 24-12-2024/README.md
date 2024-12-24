# Linux Kernel Debugging - Day 3
---

## 1. Kdump

kdump is a powerful feature within the Linux kernel designed to capture a memory image (known as a "vmcore") when a kernel crash occurs. This memory snapshot provides invaluable information for debugging and understanding the root cause of the crash.

* Enable following configuration in `.config` file
```bash
Kernel config file: /boot/config-6.5.9-dbg1
checking for CONFIG_KEXEC             [OK]
checking for CONFIG_KEXEC_CORE        [OK]
checking for CONFIG_CRASH_CORE        [OK]
checking for CONFIG_SYSFS             [OK]
checking for CONFIG_DEBUG_INFO        [OK]
checking for CONFIG_CRASH_DUMP        [OK]
checking for CONFIG_PROC_VMCORE       [OK]
checking for CONFIG_RELOCATABLE       [OK]
```
* Allocate the crashkernel size in `/etc/default/grub` file. [`crashkernel=512M`]
```bash
GRUB_TIMEOUT=5
GRUB_DISTRIBUTOR="$(sed 's, release .*$,,g' /etc/system-release)"
GRUB_DEFAULT=saved
GRUB_DISABLE_SUBMENU=true
GRUB_TERMINAL_OUTPUT="console"
GRUB_CMDLINE_LINUX="resume=/dev/mapper/openeuler-swap rd.lvm.lv=openeuler/root rd.lvm.lv=openeuler/swap cgroup_disable=files apparmor=0 crashkernel=512M"
GRUB_DISABLE_RECOVERY="true"
```
* build and insert a buggy module to get system crash.
* Example crash module
```bash
#include <linux/module.h>
#include <linux/kernel.h>

static int myinit(void)
{
	pr_info("dump_stack myinit\n");
	dump_stack();
	pr_info("dump_stack after\n");
	return 0;
}

static void myexit(void)
{
	pr_info("panic myexit\n");
}

module_init(myinit)
module_exit(myexit)
MODULE_LICENSE("GPL");
```
* it will crash your kernel, now reboot the system. After reboot the dump file will create a file called `vmcore` in `/var/crash/<timestamp>/` 
* The `vmcore` file having a huge data in core data format. (The size of file is created based on your RAM size)
* Now examine the `vmcore` using utility called `crash`.

* Install crash
```bash
sudo apt install crash   // Debian
sudo yum install crash  // RHEL
```
* Now investigate the `vmcore`
```bash
crash /<path to vmlinux> /<path to vmcore>
```

> **_NOTE:_** The crash utility in Linux is a powerful tool for analyzing kernel core dumps or live systems. It's essentially a combination of the traditional crash command and the gdb debugger, offering a comprehensive environment for investigating kernel issues. Please look up [crash](https://docs.redhat.com/en/documentation/red_hat_enterprise_linux/8/html/managing_monitoring_and_updating_the_kernel/analyzing-a-core-dump_managing-monitoring-and-updating-the-kernel#installing-the-crash-utility_analyzing-a-core-dump) document.





