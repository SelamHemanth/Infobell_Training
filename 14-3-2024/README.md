#14-03-2024
#Topic: Threads
-----------------

* pthread is a light wait process under main process. Every process have atleast one thread.
**Note:** 
*** man 5 <API>  -> File formats and conventions
*** https://sysctl-explorer.net/  -> It contains the whole imformation of the system controlers.
* By therotically we can create unlimited threads. but, real time, it is full based on RAM (Threads are allocate memory in Stack segement ).
**Note:**
*** cat /proc/sys/kernel/threads-max   -> This path shows the maximum threads you should create.
*** kernel.threads-max -> It is a variable holds the max threads in sysctrl file.
*** nproc  -> It shows the number of cores availabke in your system.
*** ulimit -s  -> It shows the stack size.
* ps -LA -> Is shows the PID of every thread.
* If main die while running threads, all threads are in live, main becomes zombie.
* pthread_join(); -> It eliminates the zombie process , it work like wait();
* pthread_tryjoin_np()  -> Normally,  pthread_join(); is blocking state. pthread_tryjoin_np() elimates the blocking state with timing options using pthread_timedjoin_np();
* getconf GNU_LIBPTHREAD_VERSION -> NPTL 2.31 -> Version of pthtred.
***Thread Safty***
* Thread Local Storage (TLS) -> Each thread gets it's own copy of the variables declared with this specifier  ( __thread ).
* __thread -> this keyword is immediatly follow by the static and extern keyword.

***Thread Cancel***
* pthread_cancel(pthread_t name);  -> It cancel the thread by using thread ID.
 
#PThread Synchrozition
---
**Whenever performing multi threading process. The automic vasriables are share to all threads. While accessing the variable ,their is a possible to ***race condition***.**
There are three methods to avoid race condition.
	- mutex
	- semaphores
	- signals

***Mutex***
Mutex is a locking mechanism , which locks and unlocks the threads. Allows single thread at a time.

 $ $ $ $ $
___________
\  $ $ $  /
 \  $ $  /
  \  $  /
   \   /
    | |
    | |
    - -
     $

* pthread_mutex_init: Initializes a mutex object.
	* Syntax: int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
	* Description: This function initializes the mutex object referenced by mutex with attributes specified by attr.
* pthread_mutex_destroy: Destroys a mutex object.
	* Syntax: int pthread_mutex_destroy(pthread_mutex_t *mutex);
	* Description: This function destroys the mutex object referenced by mutex, releasing any resources associated with it.
* pthread_mutex_lock: Locks a mutex object.
	* Syntax: int pthread_mutex_lock(pthread_mutex_t *mutex);
	* Description: This function locks the mutex referenced by mutex. If the mutex is already locked by another thread, the calling thread will block until it can acquire the lock.
* pthread_mutex_trylock: Tries to lock a mutex object without blocking.
	* Syntax: int pthread_mutex_trylock(pthread_mutex_t *mutex);
	* Description: This function tries to lock the mutex referenced by mutex without blocking. If the mutex is already locked by another thread, it returns immediately with an error.
* pthread_mutex_unlock: Unlocks a mutex object.
	* Syntax: int pthread_mutex_unlock(pthread_mutex_t *mutex);
	* Description: This function unlocks the mutex referenced by mutex, allowing other threads to acquire the lock.
* pthread_mutexattr_init: Initializes a mutex attributes object.
	* Syntax: int pthread_mutexattr_init(pthread_mutexattr_t *attr);
	* Description: This function initializes the mutex attributes object referenced by attr with default attribute values.
* pthread_mutexattr_destroy: Destroys a mutex attributes object.
	* Syntax: int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
	* Description: This function destroys the mutex attributes object referenced by attr, releasing any resources associated with it.
* pthread_mutexattr_gettype: Gets the type of a mutex attributes object.
	* Syntax: int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *type);
	* Description: This function retrieves the type of mutex referenced by attr and stores it in the integer pointed to by type.
* pthread_mutexattr_settype: Sets the type of a mutex attributes object.
	* Syntax: int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
	* Description: This function sets the type of mutex referenced by attr to the value specified by type.
* 

#pthread api's following with description
pthread_attr_destroy: Destroys a thread attributes object.
pthread_getname_np: Gets the name of a thread.
pthread_attr_getaffinity_np: Gets the CPU affinity of a thread attributes object.
pthread_getschedparam: Gets scheduling parameters for a thread.
pthread_attr_getdetachstate: Gets the detach state attribute of a thread attributes object.
pthread_join: Joins with a terminated thread.
pthread_attr_getguardsize: Gets the guard size attribute of a thread attributes object.
pthread_kill: Sends a signal to a specified thread.
pthread_attr_getinheritsched: Gets the inheritance scheduling attribute of a thread attributes object.
pthread_kill_other_threads_np: Sends a signal to other threads in the process.
pthread_attr_getschedparam: Gets the scheduling parameters attribute of a thread attributes object.
pthread_attr_getschedpolicy: Gets the scheduling policy attribute of a thread attributes object.
pthread_attr_getscope: Gets the contention scope attribute of a thread attributes object.
pthread_attr_getstack: Gets the stack attribute of a thread attributes object.
pthread_attr_getstackaddr: Gets the stack address attribute of a thread attributes object.
pthread_attr_getstacksize: Gets the stack size attribute of a thread attributes object.
pthread_attr_init: Initializes a thread attributes object with default values.
pthread_attr_setaffinity_np: Sets the CPU affinity attribute of a thread attributes object.
pthread_attr_setdetachstate: Sets the detach state attribute of a thread attributes object.
pthread_attr_setguardsize: Sets the guard size attribute of a thread attributes object.
pthread_attr_setinheritsched: Sets the inheritance scheduling attribute of a thread attributes object.
pthread_attr_setschedparam: Sets the scheduling parameters attribute of a thread attributes object.
pthread_attr_setschedpolicy: Sets the scheduling policy attribute of a thread attributes object.
pthread_attr_setscope: Sets the contention scope attribute of a thread attributes object.
pthread_attr_setstack: Sets the stack attribute of a thread attributes object.
pthread_attr_setstackaddr: Sets the stack address attribute of a thread attributes object.
pthread_attr_setstacksize: Sets the stack size attribute of a thread attributes object.
pthread_cancel: Cancels the execution of a thread.
pthread_cleanup_pop: Removes the routine from the calling thread's cancellation cleanup stack.
pthread_cleanup_pop_restore_np: Removes the routine from the calling thread's cancellation cleanup stack and saves the current cancellation cleanup state.
pthread_cleanup_push: Adds a routine to the calling thread's cancellation cleanup stack.
pthread_cleanup_push_defer_np: Adds a routine to the calling thread's cancellation cleanup stack with deferred execution.
pthread_create: Creates a new thread.
pthread_detach: Marks a thread as detached.
pthread_equal: Compares two thread identifiers.
pthread_exit: Terminates the calling thread.
pthread_getaffinity_np: Gets the CPU affinity mask of a thread.
pthread_getattr_default_np: Gets the default thread attributes.
pthread_getattr_np: Gets the attributes of a specified thread.
pthread_getconcurrency: Gets the concurrency level.
pthread_getcpuclockid: Gets the clock ID for the CPU-time clock of a thread.
pthread_yield: Suspends execution of the calling thread to allow other threads to run.
pthread_setname_np: Sets the name of a thread.
pthread_setschedparam: Sets the scheduling parameters of a thread.
pthread_setschedprio: Sets the scheduling priority of a thread.
pthread_sigmask: Examines and changes a thread's signal mask.
pthread_sigqueue: Sends a signal to a specified thread.
pthread_spin_destroy: Destroys a spin lock.
pthread_spin_init: Initializes a spin lock.
pthread_spin_lock: Locks a spin lock.
pthread_spin_trylock: Attempts to lock a spin lock.
pthread_spin_unlock: Unlocks a spin lock.
pthread_testcancel: Tests whether cancelation is pending for the calling thread.
pthread_timedjoin_np: Waits for the termination of another thread until a specified time.
pthread_tryjoin_np: Attempts to join with a terminated thread.
pthread_setcancelstate: Sets the cancelability state of the calling thread.
pthread_setcanceltype: Sets the cancelability type of the calling thread.
pthread_setconcurrency: Sets the level of concurrency.
pthread_setaffinity_np: Sets the CPU affinity mask of a thread.
pthread_setattr_default_np: Sets the default thread attributes.
pthreads: Not a system call. This is just a reference to the POSIX threads library itself.
pthread_self: Returns the thread ID of the calling thread.
These calls are used for managing threads in a POSIX-compliant operating system.
