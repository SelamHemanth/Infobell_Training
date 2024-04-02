#Date: 25-3-2024

#Topic: Memory Bugs and Debugging tools
---


#Helgrind
---
	* This tool is used to detect the race conditions in multitheading progrsmming.


#Valgrind
---
	* This tool is iused to avoid the memory leak.
	* It is not tracks the run time dynamic memory allocated bugs
	* MMAP_THRESHOLD   -> It is a macro having size (i.e., 125KB) , this is used to allocate the memory with dynamically.
	* If the size is below MMAP_THRESHOLD , heap segment is allocated.
	* mlock()  -> It is locks the allocated  memory .
	* alloca()  -> It is system call which is allocates the dynamic memory as same like malloc().Main the advantage is automaically delloactes the memory like free().
		#include <alloca.h>
	         void *alloca(size_t size);
	* vgdb (valgrind gnu debugger) is tool like gdb.
	* electric fence   -> It is a memory debugginf tools.
	* lcov    	   -> It is  a  graphical front-end for GCC's coverage testing tool gcov.


#Sanitizer Tool
---
***Addresssanitizer***
	* memory error detecter
	* -fsanitize=address

***Kernelsanitizer***
	* memory error detecter
	* -fsanitize=kernel-address

***Memorysanitizer***
	* Uninitilized memory reads detector
	* -fsanitize=memory-fPIE -pie

***Threadsanitizer***
	* data race detector
	* -fsanitize=thread

***leaksanitizer***
	* memory leak detector
	* -fsanitize=leak

 

