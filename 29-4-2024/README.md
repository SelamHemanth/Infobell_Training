#Memory Management
---

***Cont  kmalloc***
---

 * The ksize API, given a pointer to slab-allocated memory (in effect, memory allocated via the kmalloc), returns the actual number of bytes allocated.
size_t ksize(const void *objp);
 * It could be more than what was requested. F.e.

```javascript
size_t actual=0;
void *ptr = kmalloc(160, GFP_KERNEL); // ask for 160 bytes
actual = ksize(ptr); // will get 192 bytes (actual ← 192)
Thus, ksize() helps us detect the wastage (internal fragmentation)!
```
 * The way to check which slabs suffer from wastage: use the kernel’s slabinfo utility
 * Note: By using `sudo vmstat -m` , we can see the chache page sizes.

***vmalloc***
---

 * When you require more memory than kmalloc can provide (typically 4 MB). vmalloc provides a virtually contiguous memory region.  max size depends on the hardware platform and the kernel config; the kernel’s.
 * VMALLOC region size – a global pool for all vmalloc’s, only for software use (f.e. not ok for DMA transfers); only process context (not in interrupt code); might cause process context to block.
 * slower (page table setup required, unlike the kmalloc). the page frames corresponding to the virtual memory region allotted are indeed allocated immediately (under the hood, via alloc_pages() - page allocator!).

```javascipt
void *vmalloc(unsigned long size);
void *vzalloc(unsigned long size); // recommended !
void vfree(const void *addr);
```
 * The vmalloc() is used by the kernel to allocate thread stacks when VMAP_STACK=y.

***Custom Slab Cahche***
---

 * If a data structure in your kernel code is very often allocated and de-allocated, it’s perhaps a good candidate for a custom slab cache.
 * Slab layer exposes APIs to allow custom cache creation and management.

 * Managed memory for drivers with the devres APIs (1)
	* Devres : device resources manager
	* A framework developed for the device model, enabling autofreeing of memory allocated via the ‘devres’ APIs
	* The freeing occurs on driver detach
	* Requires the struct device pointer though

In place of        |       Devres API
-------------------|-----------------------------
kmalloc / kzalloc  |   devm_kmalloc /devm_kzalloc
dma_alloc_coherent |   dmam_alloc_coherent

 * Kernel Segment on the x86_64:

 ![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/29-4-2024/Kernel%20Segment.PNG)

 * Literally watch memory usage change over time with:
```javascript
watch -n 5 -d '/bin/free -m'
```

	* -n : update interval in seconds
	* -d : Highlight the differences between successive updates...


***The OOM (Out Of Memory) Killer***
---

 *  Where’s the VM?
	* In the ‘memory pyramid’
	* Registers, CPU Caches, RAM, Swap, (+ newer: nvdimm’s)
 * What if – worst case scenario - all of these are completely full!?
 * Then the OOM Killer jumps in, and
	* Kills the process (and descendants) with highest memory usage
	* Uses heuristics to determine the target process
 * Then the OOM Killer jumps in, and
	* Kills the process (and descendants) with highest memory usage
	* Uses heuristics to determine the target process
 * OOM Score (in /proc/<pid>/oom_score)

***SCHEDULING***
---

 ![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/29-4-2024/Linux%20State%20Machine.PNG)

 * The very powerful and useful Linux perf – performance monitoring and analysis – tool lets us “see” a map of processes (threads) as they run on various processor cores. Below is some sample output from running the 'perf sched map' command from a previously grabbed
```javascript
 $ perf sched record <command>
 $ perf sched map   	//to see complete system
```
 * Want it more visual? No problem. The 'perf timechart' command interprets the perf data file (output by the previous 'perf sched record <command>' command and renders the visual representation as an SVG image file.
 * Use the kernel ftrace (raw) or the trace-cmd front-end or kernelshark to collect data samples.
 
***Linux and Real-Time***
---

 * Firstly, the Linux OS as originally designed and implemented, is not a “hard real-time” OS, as in an RTOS (Real-Time-OS; more follows on this below: see the sidebar on the PREEMPT-RT patch).
 * Vanilla-Linux as such is a GPOS (a General-Purpose-OS, like Windows, Mac, Unix'es, etc).
		
 ![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/29-4-2024/os%20types.PNG)

**Soft Realtime Capabilities**:
---

 * However, the (vanilla) Linux OS's performance metrics are easily high enough to have it qualify as an eminently capable soft real-time (SRT) system. This basically means that it cannot guarantee to meet every single deadline; rather, it performs on a best-effort basis. SRT is exactly the kind of system required for many applications in the real world, many being within the consumer electronics domain.
 * The POSIX standard specifies three scheduling policies, one of which is the “usual” or normal policy and is always the default. The other two are (soft) realtime scheduling policies. They are:
	* SCHED_NORMAL (or SCHED_OTHER) ← Default scheduling policy
	* SCHED_RR
	* SCHED_FIFO

**1.SCHED_FIFO:**
 * A running SCHED_FIFO task can only be preempted under the following three conditions:
	* It (in)voluntarily yields the processor (technically, it moves out from the RUNNING/RUNNABLE state); this happens when a task issues a blocking call or invokes a system call like sched_yield(2)
	* It dies or stops
	* A higher priority realtime task becomes runnable.
 * In the first case above, the task is then placed at the end of it's runqueue (for that priority level). In the third case, the task remains at the head of the runqueue for it's priority level.

**2.SCHED_RR:**
 *  behaviour is identical to that of SCHED_FIFO above except that:
	* It has a timeslice, and will thus (also) be preempted when it's timeslice expires
	* When preempted, the task is moved to the tail of the runqueue for it's priority level, ensuring that all SCHED_RR tasks at the same priority level are executed in turn.

**3.SCHED_OTHER / SCHED_NORMAL:**
 * All threads run with this policy by default. It is a decidedly non-realtime policy, the emphasis being on “fairness and overall throughput”. It's implementation from kernel ver 2.6.0 upto 2.6.22 was via the so called “O(1) scheduler”; from 2.6.23 onward, it's implemented via the scheduling class called CFS.

---


**Note:** On an SMP box, the threads will still run “as usual” - all together, in paralle. To prevent this (and see the point of this application), disable all processors but one to see the true effect of this demo.
	There are (at least) two ways to do this:
```javascript
 $ sysfs    //As root, write '0' to the sysfs node (file) representing the online state of a CPU you wish to disable.
 $ taskset  //The taskset utility lets a user set (and query) the CPU affinity mask of a process.
```

***The chrt utility***
---

 * chrt(1) sets or retrieves the real-time scheduling attributes of an existing PID or runs COMMAND with the given attributes. Both policy (one of SCHED_OTHER, SCHED_FIFO, SCHED_RR, or SCHED_BATCH) and priority can be set and retrieved.
```javascript
 $ chrt -f -p 50 6878 	// Make PID 6878 SCHED_FIFO pri 50
 $ chrt -m		// Show priority range
 $ chrt -r -p 6878	// pid 6878's current scheduling policy: SCHED_FIFO
			// pid 6878's current scheduling priority: 99
 $ chrt -r -p 10 6878 	// set prio to 10...
```

***Scheduler Classes***
---

 * The Linux scheduler is modular, enabling different algorithms to schedule different types of processes. This modularity is called scheduler classes.
 * Scheduler classes enable different, pluggable algorithms to coexist, scheduling their own types of processes / threads. Each scheduler class has a priority. The base scheduler code, which is defined in kernel/sched/core.c , iterates over each scheduler class in order of priority. (In practice, the scheduling classes reside on a linked list that is followed). The highest priority scheduler class that has a runnable process wins, selecting who runs next.The Completely Fair Scheduler (CFS) is the registered scheduler class for normal processes, called SCHED_NORMAL in Linux (and SCHED_OTHER in POSIX). CFS is defined in kernel/sched_fair.c.
 * The currently existing (as of 6.4) scheduler classes, in priority order, are:

	 	Class Name	 |	sched_class Data Structure	|	 Name Defined in
	 ************************|**************************************|***************************
	     Stop-sched *        |     stop_sched_class			| kernel/sched/stop_task.c
	     Deadline + 	 |     dl_sched_class			| kernel/sched/deadline.c
	     RT (Real-Time) 	 |     rt_sched_class 			| kernel/sched/rt.c
	     CFS 	         |     fair_sched_class			| kernel/sched/fair.c
	     Idle 		 |     idle_sched_class			| kernel/sched/idle_task.c

***CFS***
---

 * CFS stands for "Completely Fair Scheduler," and is the new "desktop" process scheduler implemented by Ingo Molnar and merged in Linux 2.6.23. It is the replacement for the previous vanilla scheduler's SCHED_OTHER interactivity code.
 * 80% of CFS's design can be summed up in a single sentence: CFS basically models an "ideal, precise multi-tasking CPU" on real hardware."Ideal multi-tasking CPU" is a (non-existent :-)) CPU that has 100% physical power and which can run each task at precise equal speed, in parallel, each at 1/nr_running speed. For example: if there are 2 tasks running, then it runs each at 50% physical power i.e., actually in parallel.
 * On real hardware, we can run only a single task at once << the famous Von Neumann bottleneck: we can only run one machine instruction at a time on the processor >>, so we have to introduce the concept of "virtual runtime." The virtual runtime of a task specifies when its next timeslice would start execution on the ideal multi-tasking CPU described above. In practice, the virtual runtime of a task is its actual runtime normalized to the total number of running tasks.

 * **FEW IMPLEMENTATION DETAILS**: In CFS the virtual runtime is expressed and tracked via the per-task p->se.vruntime (nanosec-unit) value. This way, it's possible to accurately timestamp and measure the "expected CPU time" a task should have gotten.
	* The vruntime variable stores the virtual runtime of a process, which is the actual runtime (the amount of time spent running) normalized (or weighted) by the number of runnable processes. The virtual runtime’s units are nanoseconds and therefore vruntime is decoupled from the timer tick.Because processors are not capable of perfect multitasking and we must run each process in succession, CFS uses vruntime to account for how long a process has run and thus how much longer it ought to run.

 * CFS's task picking logic is based on this p->se.vruntime value and it is thus very simple: it always tries to run the task with the smallest p->se.vruntime value (i.e., the task which executed least so far). CFS always tries to split up CPU time between runnable tasks as close to "ideal multitasking hardware" as possible.
 * Most of the rest of CFS's design just falls out of this really simple concept, with a few add-on embellishments like nice levels, multiprocessing and various algorithm variants to recognize sleepers.

***Scheduling Latency***
---

 * The kernel guarantees that every runnable task will run at least once in a given time interval. This interval is called the scheduling latency.The scheduling latency is a system configurable parameter, a sysctl named sched_latency (used to be called sched_latency_ns):
 * Eg. on a recent 5.15 kernel:
```javascript
$ grep sched_latency /sys/kernel/debug/sched/debug
	.sysctl_sched_latency : 24.000000
```

