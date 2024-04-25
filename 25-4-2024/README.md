****Memory Management****
---

 * The memory mapping is the main important in kernel internals, Basically all are virtual memories.
 * The page table is convert the virtual memory to physical memory or Viseversa.
 * Memory is virtualized
        * Programmer does not worry about phy RAM, availability, etc
 * Information Isolation
        * Each process run’s in it’s own private VAS
 * Fault Isolation
        One process crashing will not cause others to be affected. Multithreaded (firefox) vs multiprocess (chrome)

***16-bit ➠ 1 Level Paging:***
---

        * The one level paging is a process to find the physical address of the bit.

![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/os_essentials-6.gif)

                ` Virtual Adress = ( ( Page address * page size ) + offset address ) `
***32-bit ➠ 2 Level Paging:***
---

        * This picture gives the clear explanation how the 2 level paging is process.

 ![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/linear%20address%202%20level%2032-bit.PNG)

***64-bit ➠ 4 Level , 5 Level Paging:***
---

        * This picture gives the clear explanation how the 4 level paging is process.

 ![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/linear%20address%204%20level%2064-bit.PNG)

***CPU Cache***
---

	* The CPU Caches are very fast memory units, which is inside the CPU. Their are different level of cahces with different type speed and cycles.
	* This figure gives the clear picture.
 * **False Sharing**
	* “Avoiding and Identifying False Sharing Among Threads”, Intel In symmetric multiprocessor (SMP) systems, each processor has a local cache.The memory system must guarantee cache coherence. False sharing occurs when pthreads on different processors modify variables that reside on the same cache line.
	* This invalidates the cache line and forces an update, which hurts performance.
	* Prevented by ensuring the variables cannot “live” in the same CPU cacheline

 ![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/Memory%20Latency.PNG)

 * This is the size of the chache:
```javascript
  $ getconf -a | grep CACHE_LINE
LEVEL1_ICACHE_LINESIZE             64
LEVEL1_DCACHE_LINESIZE             64
LEVEL2_CACHE_LINESIZE              64
LEVEL3_CACHE_LINESIZE              64
LEVEL4_CACHE_LINESIZE              0
```
 * This is the different level of cache sizes:
```javascript
   $ getconf -a | grep CACHE
LEVEL1_ICACHE_SIZE                 65536
LEVEL1_ICACHE_ASSOC                2
LEVEL1_ICACHE_LINESIZE             64
LEVEL1_DCACHE_SIZE                 65536
LEVEL1_DCACHE_ASSOC                2
LEVEL1_DCACHE_LINESIZE             64
LEVEL2_CACHE_SIZE                  524288
LEVEL2_CACHE_ASSOC                 16
LEVEL2_CACHE_LINESIZE              64
LEVEL3_CACHE_SIZE                  16777216
LEVEL3_CACHE_ASSOC                 16
LEVEL3_CACHE_LINESIZE              64
LEVEL4_CACHE_SIZE                  0
LEVEL4_CACHE_ASSOC                 0
LEVEL4_CACHE_LINESIZE              0
```
 * Their is a utility called `lstopo` to show the in depth picture of your system socket design.

```javascript
 //Install utility by using this command 
 $ sudo apt install hwloc
 //run this commad
 $ lstopo
```
 * Example output:
 
![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/lstopo.PNG)

 * Software developers would do well to be aware how programming in a cacheaware manner can greatly optimize code:
	* keep all important structure members (‘hotspots’) together and at the top
	* ensure the structure memory start is CPU cacheline-aligned
	* don’t let a member “fall off” a cacheline (use padding if required compiler can help)  

***Virtual Address Space Splitting***
---

 * VM split is a kernel configurable!
 * In./arch/x86/Kconfig: VMSPLIT_3G / VMSPLIT_2G/VMSPLIT_1G
 * x86_32: VM split is at 3 GB
 * ARM-32: VM split is at either 2 GB or 3 GB
 * On 32-bit Linux,as a simpler example to begin with…

![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/vm-split.PNG)

 * So, the 64-bit VAS on the x86_64 – with typically 48-bit addressing – is as follows:

![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/64%20bit%20vm%20split.PNG)

![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/virtual%20memory%20split.PNG)

***PAGE_OFFSET***
---

 * Splitting point, or, on 64-bit, the start of the kernel segment, is called PAGE_OFFSET.More technically, it’s the location from which physical RAM is direct-mapped into kernel VAS
```javascript
  $ zcat /proc/config.gz |grep -i VMSPLIT

CONFIG_VMSPLIT_3G=y
# CONFIG_VMSPLIT_2G is not set
# CONFIG_VMSPLIT_1G is not set
```

***Linux OS at Boot***
---

 * RAM is divided into nodes. One node for each CPU core that has local RAM available to it. A node is represented by the data structure pg_data_t.
 * Each node is further split into (at least one, upto four) zones.
	* ZONE_DMA
	* ZONE_DMA32
	* ZONE_NORMAL
	* ZONE_HIGHMEM
 * Each zone consists of page frames. A page frame is represented (and managed) by the data structure page.
 * **Zones:**
	* Often enable a workaround over a hardware or software issue.
	* Eg.
		* ZONE_DMA : 0 – 16 MB on old Intel with the ISA bus
 		* ZONE_HIGHMEM : what if the 32-bit platform has more RAM than there is kernel address space? (eg. an embedded system with 3 GB RAM on a machine with a 3:1 VM split) and so on.
	* The ‘lowmem’ region – direct mapped platform RAM – is often placed as ZONE_NORMAL (but not always)
	* Kernel inits zones at boot

***Linux Kernel Memory Allocation***
---

