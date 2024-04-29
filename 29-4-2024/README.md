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


