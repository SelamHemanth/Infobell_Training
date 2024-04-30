# CGROUPS
---

 * A cgroup is a logical grouping of processes that can be used for resource management in the kernel. Once a cgroup has been created, processes can be migrated in and out of the cgroup via a pseudo-filesystem API.
 * See all the Cgroups:
```javascript
 $ cat /proc/cgroups

#subsys_name    hierarchy       num_cgroups     enabled
cpuset  6       1       1
cpu     5       130     1
cpuacct 5       130     1
blkio   11      130     1
memory  8       248     1
devices 12      130     1
freezer 4       8       1
net_cls 2       1       1
perf_event      3       1       1
net_prio        2       1       1
hugetlb 7       1       1
pids    9       142     1
rdma    10      1       1

 $ lssubsys        // sudo apt install cgroup-tools

cpuset
cpu,cpuacct
blkio
memory
devices
freezer
net_cls,net_prio
perf_event
hugetlb
pids
rdma
```
 * The CPU controller mechanism allows a system manager to control the percentage of CPU time given to a cgroup. The CPU controller can be used both to guarantee that a cgroup gets a guaranteed minimum percentage of CPU on the system, regardless of other load on the system, and also to set an upper limit on the amount of CPU time used by a cgroup, so that a rogue process can't consume all of the available CPU time.
 * CPU scheduling is first of all done at the cgroup level, and then across the processes within each cgroup. As with some other controllers, CPU cgroups can be nested, so that the percentage of CPU time allocated to a top-level cgroup can be further subdivided across cgroups under that top-level cgroup.
 * The memory controller mechanism can be used to limit the amount of memory that a process uses. If a rogue process runs over the limit set by the controller, the kernel will page out that process, rather than some other process on the system..
 * `Systemd` can specify cgroup parameters when launching services at boot!
```javascript
 $ man systemd.resource-control
```
 
**Note:** For more details, please go through [`CGroup`](https://github.com/SelamHemanth/Infobell_Training/blob/main/22-4-2024/InfobellIT_LinuxKernel_Apr2024_kaiwanTECH_6d/courseware/mod08_task_scheduler/cgroups.pdf) document.

***Kernel Synchronizing Locking***
---

 * Kernel synchronization locking is a vital concept in operating systems, especially those with multiple processors (multiprocessing). It ensures that multiple parts of the operating system kernel, which is the core of the OS, can access and modify shared data structures safely and consistently.

 * Here's a breakdown of the key points:
 * `Why Locking?`
	*  The kernel juggles tasks from various applications and handles system events concurrently. Without proper locking, issues like race conditions can arise. A race condition happens when multiple parts of the code try to access and modify the same data at the same time, potentially leading to unexpected results or crashes.
 * `Types of Locks:`The Linux kernel, a popular example, offers various locking mechanisms for developers to choose from based on the specific situation. Some common ones include:
	* **Spinlocks:** These busy-wait locks prevent other parts of the code from accessing the data until the current holder releases it.
	* **Semaphores:** Similar to spinlocks, but instead of busy waiting, they put the requesting process to sleep until the lock becomes available.
	* **Mutexes:** Mutual exclusion locks ensure only one process can access the data at a time, even across multiple processors.
	* **Read-Copy-Update (RCU):** This technique allows lock-free reads of data structures with safe updates through a temporary copy.
 * `Benefits of Proper Locking:`
	* **Data Integrity:** Ensures data structures maintain consistency and avoid corruption.
	* **Stability:** Prevents race conditions and unexpected system crashes.
	* **Concurrency:** Enables safe concurrent access to shared resources by the kernel.

**Note:** For more details, please go through [`kernel synchronizing locking`](https://github.com/SelamHemanth/Infobell_Training/blob/main/22-4-2024/InfobellIT_LinuxKernel_Apr2024_kaiwanTECH_6d/courseware/mod09_kernel_sync_locking.pdf) document.

  
