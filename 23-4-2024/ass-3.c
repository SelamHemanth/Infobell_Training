//Enhance the above kernel module to print out some process-context information; for example, print out the process name, PID (actually TGID), VM information (look up some members of the mm_struct, like start_data, end_data, etc etc).Also: print the kernel virtual addresses of some variables in the module.Print the current value of jiffies as well.
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/sched/signal.h>
#include <linux/jiffies.h>

MODULE_LICENSE("Dual BSD/GPL");

static int __init hello_init(void)
{
    printk(KERN_CRIT "******************** Inserting the Module **************\n");
    printk(KERN_INFO "Process name: %s\n", current->comm);
    printk(KERN_INFO "Process ID (TGID): %d\n", current->tgid);

    struct mm_struct *mm = current->mm;
    if (mm) {
        printk(KERN_INFO "VM Information:\n");
        printk(KERN_INFO "  start_data: 0x%lx\n", mm->start_data);
        printk(KERN_INFO "  end_data: 0x%lx\n", mm->end_data);
    }
    static int Hemanth = 1;
    printk(KERN_INFO "Kernel virtual address of my_variable: 0x%px\n", &Hemanth);

    printk(KERN_INFO "Current value of jiffies: %lu\n", jiffies);
    return 0; /* success */
}

static void __exit hello_exit(void)
{
    printk(KERN_CRIT "********************* Removing the Module **************\n");
    printk(KERN_INFO "Process name: %s\n", current->comm);
    printk(KERN_INFO "Process ID (TGID): %d\n", current->tgid);
}

module_init(hello_init);
module_exit(hello_exit);

/* OUTPUT:
 * sudo insmod ass-3.ko
 * sudo journalctl -k --since="2 min ago"
 * Apr 28 10:11:55 hemanthdev kernel: ******************** Inserting the Module **************
 * Apr 28 10:11:55 hemanthdev kernel: Process name: insmod
 * Apr 28 10:11:55 hemanthdev kernel: Process ID (TGID): 449573
 * Apr 28 10:11:55 hemanthdev kernel: VM Information:
 * Apr 28 10:11:55 hemanthdev kernel:   start_data: 0x560e308dcc10
 * Apr 28 10:11:55 hemanthdev kernel:   end_data: 0x560e308de080
 * Apr 28 10:11:55 hemanthdev kernel: Kernel virtual address of my_variable: 0xffffffffc0c02010
 * Apr 28 10:11:55 hemanthdev kernel: Current value of jiffies: 4401298724
 *
 * sudo rmmod ass-3.ko
 * sudo journalctl -k --since="2 min ago"
 * Apr 28 10:15:59 hemanthdev kernel: ********************* Removing the Module **************
 * Apr 28 10:15:59 hemanthdev kernel: Process name: rmmod
 * Apr 28 10:15:59 hemanthdev kernel: Process ID (TGID): 451049
 */


