#Date : 26-3-2024

#Topic : Debugging
---

***GDB Debugging***
---
	* GNU GDB Debugger is a debugging tool, it trace the code while running time.
	* To enable the debugging utilities to compile the a source code with the option -g.
	* $ gcc -g abc.c
	* $ gdb ./a.out  -> It opens in terminal mode
	* $ gdb -tui ./a.out   -> It opens in text user interface
**Start debugging :** :
---
	* l -> list out the 10 lines of souuce code
	* b -> putting break points
		b <line number>    or     b  <function name>
	* r -> run the code
		r <parameters>  -> if you want to pass parameters to main.
	* p -> print the values of a variables
		By default it will print octal. 
	 	* p/x <variable>  -> It print as hexa.
		* set print pretty -> It enables the printing line by linedisplaying. 
	* s -> step by step execute
	* n -> set out to next function
	* bt -> back trace to examine the stack.
	* display -> It continuosly displays the variable value
	* disassemple -> It prints the code in assembly language
	* set variable <variable name> = <value>   -> To change variable value while running time (It is temporary change only)
	* show can-use-hw-watchpoints -> It shows the status of the hardware watchpoint.
	* watch <variable> -> It shows the variable value before and after change.
	* enable/disable <breakpoint> -> It enables or disables the breakpoints or watchpoints temparerly.
	* info threads  -> It shows all threads in code with thread number.
	* thread <num>  -> switch into threads with its number.
	* thread apply all <cmd> -> To apply all threads
		* thread apply all bt -> To see the stack trace of all threads.   

Note :   * Don't compile with -O (To ignore Optimise use this option -O0 while compiling).
	 * GNU GDB Debugger is not supports to debug macros. 
	 * You can find more gdb commands through this link https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf
 
#Core Dump
---
 	A core dump, also known as a core file, is a file that contains the memory image of a running process when it crashes due to a segmentation fault, illegal instruction, or other fatal error. Core dumps are useful for debugging because they allow developers to inspect the state of the crashed program, including memory contents, stack traces, and register values.

***Test Core Dump*** ::
	* When you run buggy core , it results Segmentation fault . But, it is not shows any core file.
	* To generate core dump file. We need to setup some limits to unlimited.
	* Initially ulimit is 0 . we need to set unlimited by using this command.
		* $ uname -c unlimited
	* Then run the buggy code . Now you can notice core dump file.
		* Segmentation fault (core dumped)
	* And, also it creates the dump file in current working directory.
	* You also change your core_pattern like this (switch into root user  -> sudo -i) 
		* ~# echo "core_%p_%s_%e" > /proc/sys/kernel/core_pattern
	* If you restart your system , It goes to default (i.e., reset automatically)
	* If don't want to change , by using following command fix it permanently (switch into root user  -> sudo -i).
		* ~# sysctl -w "kernel.core_pattern=core_%h_%p_%u_%s_%e"

#perf
---
	perf is a tool which is used to CPU performance monitor.

	* sudo perf stat  -> It shows the statistics of the CPU.
	* sudo perf top  -> It shows the run time CPU usage of all processes with exact running job
	* sudo perf record  -> It records the all events in your system and creats perf.data binary file.
	* sudo perf report   -> It shows the all the recorded data.
	
	
