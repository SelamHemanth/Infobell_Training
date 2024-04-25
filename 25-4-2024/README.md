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

***16-bit   ->  1 Level Paging:***
---
        * The one level paging is a process to find the physical address of the bit.

![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/os_essentials-6.gif)

                ` Virtual Adress = ( ( Page address * page size ) + offset address ) `
***32-bit   ->  2 Level Paging:***
---
        * This picture gives the clear explanation how the 2 level paging is process.

 ![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/linear%20address%202%20level%2032-bit.PNG)

***64-bit   -> 4 Level , 5 Level Paging:***
---
        * This picture gives the clear explanation how the 4 level paging is process.

 ![image](https://github.com/SelamHemanth/Infobell_Training/blob/main/25-4-2024/linear%20address%204%20level%2064-bit.PNG)


