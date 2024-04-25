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

***16-bit   --->  1 Level Paging:***
---

        * The one level paging is a process to find the physical address of the bit.

![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/os_essentials-6.gif)

                ` Virtual Adress = ( ( Page address * page size ) + offset address ) `
***32-bit   --->  2 Level Paging:***
---

        * This picture gives the clear explanation how the 2 level paging is process.

 ![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/linear%20address%202%20level%2032-bit.PNG)

***64-bit   ---> 4 Level , 5 Level Paging:***
---

        * This picture gives the clear explanation how the 4 level paging is process.

 ![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/linear%20address%204%20level%2064-bit.PNG)

***CPU Cache***
---

	* The CPU Caches are very fast memory units, which is inside the CPU. Their are different level of cahces with different type speed and cycles.
	* This figure gives the clear picture.

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


