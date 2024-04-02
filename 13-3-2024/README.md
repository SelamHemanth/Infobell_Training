#Date: 13-3-2024
#Topic: Signals

* The processor not having MMU , we can use vfork() system call, Is is also work as fork().
* The kernel coding developer follow some rules while writing code, These are available in https://www.kernel.org/doc/html/v4.10/process/coding-style.html . The tool which is checks the patch code (https://github.com/esoule/checkpatch) .
* indent -linux <source file> -> this command corrects the indents in code
.

#Zombie process
* When zombie process is stored in kernel, the only one solution to kill the died child is you need to kill the parent.

#Singals
* A signal is an integer number, to do somthing.
* The default signals are in KERNEL space.
* Total 64 singals are in linux, But 31 signals only using in UNIX, 32 - 64 singals are realtime signals (These are generic).
* man 7 signals    or    kill -l  ( shows the list of signals)
* SIGHUP signals Hangup detected on controlling terminal. If you want to ignore , use "  nohup <source file>  ".
* SIGTERM is a default signal "  SIGTERM      P1990      Term    Termination signal ".
* void (*sighandler_t)(int); is a default signal handler.
**Note:
***ap_log_error -> catches the error flow as a log file.

#Flags
* #define SA_NOCLDWAIT 2   -> do not transform children into zombies when they terminate.
* #define SA_NOCLDSTOP 1   -> do not receive notification when child processes stop.
* #define SA_RESETHAND 0x80000000  ->  Reset to SIG_DFL on entry to handler.
* #define SA_RESTART 0x80000000 ->  Restart the syscall on signal return.
* #define SA_NOMASK  -> Dont automatically block the signal when its handler is being executed.
**Note:
*** ~/stress-ng is the tool which stresses the hardware of system and generates the log.
*** ~/psiginfo is used to know whole imformation of all signals 
*** ~/prlimit is used to get and set process resource limits

#PThreads
* Threads also create a the process. but it is a light wight process.
* It create the (fork) * 5 times faster than fork system call.
**Note:
*** ~/gnome-system-monitor  -> It is a GUI CPU process monitoring tool.
*

