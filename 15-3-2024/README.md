#15-03-2024

#Topic: Synchronization Mechanisems
---
***Mutex***
---
#Note:
---
** Please check 14-03-2024.**
 * If the threads are dynamically allocated and terminated abnormally. All the stuff are in memory, it causes memory leak and etc,., bugs.
 * To avoid this problem ,we can use cleanup handler. Their are some APIs are available in linux.
	* pthread_cleanup_push,  pthread_cleanup_pop - push and pop thread cancellation clean-up handlers.
		void pthread_cleanup_push(void (*routine)(void *),void *arg);
                void pthread_cleanup_pop(int execute);
	* pthread_cleanup_push_defer_np,  pthread_cleanup_pop_restore_np -push and pop thread cancellation clean-up handlers while saving cancelability type.
		void pthread_cleanup_push_defer_np(void (*routine)(void *),void *arg);
	       void pthread_cleanup_pop_restore_np(int execute);

 * The Kernel Schedulable Entity (KSE) on the Linux OS is a thread (and not a process).
***Scheduling***
 * Scheduler have basically three types of algorithems in kernel. SCHED_NORMAL, SCHED_FIFO, SCHED_RR.
 * Real-time priority range is 1 to 99, with 99 being the highest.
 * **chrt -m** -> It shows the minimum and maximum priorities for all schedular algorithems.
 * **chrt -p <PID>  -> Is shows the thread, which algorithem is running on.
 *  pthread_setschedparam,  pthread_getschedparam - set/get scheduling policy and parameters of a thread.
 * pthread_setschedprio - set scheduling priority of a thread
***Note:***
	**taskset <choose cpu number>  <source code>  <priority number>** -> It is a way of run a code to set CPU to perform the process.
#systemctl
---
 * **systemctl isolate multi-user.target**   -> It converts the desktop graphical mode to console mode.
 * **systemctl isolate graphical.target**    -> It converts the console mode to graphical mode.


 
