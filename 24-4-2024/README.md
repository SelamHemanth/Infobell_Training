#KERNEL ARCHITECTURE AND THE PROCESS DESCRIPTOR
---

***The HZ Value***
---
 * The 2.6 Linux kernel (on x86) sets up a timer interrupt to fire once every millisecond  
 * Linux programs a timer chip, the Programmable Interval Timer (PIT- usually the 8254 chip on x86 motherboards),Nowadays, HZ is now a kernel build-time tunable (`CONFIG_HZ and variations`).
 * The value of HZ is basically a function of:
	1.the processor architecture
	2.the kernel version.
 * For example,
```javascript
$ grep "CONFIG_HZ=" /boot/config-6.1.0-lkp2e-01+
CONFIG_HZ=250
```
 * Official kernel documentation on the ‘tickless’ or dynamic ticks (dynticks) / [NO_HZ](https://www.kernel.org/doc/Documentation/timers/NO_HZ.txt)
 * It is critical to understand that for every thread that is alive on the Linux OS, the kernel maintains a corresponding “task structure”.
 * The kernel maintains two stacks (one for each privilege level) – a user-mode and a kernel-mode stack. 
 * Thus, for every thread alive on the system, we have two stacks:
	* a user-mode stack
	* a kernel-mode stack
`(The exeception to the above rule: kernel threads. Kernel threads see only kernel virtual address space; thus, they require only a kernel-mode stack).`
```javascript
$ ps -e | wc -l    -> It shows the number of processes
330
$ ps -AL | wc -l   -> It shows the numner of threads
485
```
 * **Kernel Mode Stack Size on a few architectures** 
	* a user-mode stack : dynamic, can (typically) grow to 8 MB (RLIMIT_STACK)
	* a kernel-mode stack : fixed size, static (2 pages on 32-bit / 4 pages on 64-bit)
 * Besides kernel text and data, the kernel dynamically allocates and manages space for several meta-data structures and objects, among them the memory pools, kernel stacks, paging tables, etc.
```javascript
$ grep -E "KernelStack|PageTables" /proc/meminfo
KernelStack:        7984 kB
PageTables:        12004 kB
SecPageTables:         0 kB
```
