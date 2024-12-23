# Linux Kernel Debugging - Day-2
---

## Tracing:
* ltrace (Library Tracer)
* strace (System Call Tracer)
* ftrace (Function Tracer)
* perf (Performance Events)
* eBPF (Extended Berkeley Packet Filter)
  * bcc
  * bpftrace

### 1. Ltrace
---
ltrace is a program that simply runs the specified command until it exits.  It intercepts and records the dynamic library calls which are called by the executed process and the signals which are received by that process.  It can also intercept and print the system calls executed by the program
* Install Packes
```javascript
sudo apt install ltrace   //Debian
sudo yum install ltrace   //RHEL
```
* Usage
```javascript
ltrace <executable binary>   // to trace the executable binaries
ltrace -p <PID>  // to trace the process with PID number
```
* example output:
```bash
ltrace ./a.out
puts("Hello World"Hello World
)                                                                              = 12
+++ exited (status 12) +++
```

### 2. Strace
---
strace is a useful diagnostic, instructional, and debugging tool. System administrators, diagnosticians and trouble-shooters will find it invaluable for solving problems with programs for which the source is not readily available since they do not need to be recompiled in order to trace them.  Students, hackers and the overly-curious will find that a great deal can be learned about a system and its system calls by tracing even ordinary programs. And programmers will find that since system calls and signals are events that happen at the user/kernel interface, a close examination of this boundary is very useful for bug isolation, sanity checking and attempting to capture race conditions.
* Install Packes
```javascript
sudo apt install strace   //Debian
sudo yum install strace   //RHEL
```
* Usage
```javascript
strace ./a.out  //capture the system calls
strace -e trace=openat,close ./a.out  //to filter the only open and close system calls
strace -c ./a.out  //to see the statisctics of execution
```
* example output
```bash
$ strace ./a.out
execve("./a.out", ["./a.out"], 0x7ffecb4f0840 /* 28 vars */) = 0
brk(NULL)                               = 0x564c3bc78000
arch_prctl(0x3001 /* ARCH_??? */, 0x7ffe3b5a4870) = -1 EINVAL (Invalid argument)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f971ad42000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=67027, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 67027, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f971ad31000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\237\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
pread64(3, "\4\0\0\0 \0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0"..., 48, 848) = 48
pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0I\17\357\204\3$\f\221\2039x\324\224\323\236S"..., 68, 896) = 68
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=2220400, ...}, AT_EMPTY_PATH) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2264656, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f971aa00000
mprotect(0x7f971aa28000, 2023424, PROT_NONE) = 0
mmap(0x7f971aa28000, 1658880, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x7f971aa28000
mmap(0x7f971abbd000, 360448, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1bd000) = 0x7f971abbd000
mmap(0x7f971ac16000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x215000) = 0x7f971ac16000
mmap(0x7f971ac1c000, 52816, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f971ac1c000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f971ad2e000
arch_prctl(ARCH_SET_FS, 0x7f971ad2e740) = 0
set_tid_address(0x7f971ad2ea10)         = 9195
set_robust_list(0x7f971ad2ea20, 24)     = 0
rseq(0x7f971ad2f0e0, 0x20, 0, 0x53053053) = 0
mprotect(0x7f971ac16000, 16384, PROT_READ) = 0
mprotect(0x564c3bc2f000, 4096, PROT_READ) = 0
mprotect(0x7f971ad7c000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7f971ad31000, 67027)           = 0
newfstatat(1, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}, AT_EMPTY_PATH) = 0
getrandom("\x9a\xf3\x61\x89\xec\xfc\x58\xc1", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x564c3bc78000
brk(0x564c3bc99000)                     = 0x564c3bc99000
write(1, "Hello World\n", 12Hello World
)           = 12
exit_group(12)                          = ?
+++ exited with 12 +++
```

### 3. Ftrace
---
The perf ftrace command provides a collection of subcommands which use kernel’s ftrace infrastructure.

Note: Enable the trace in configuration of kernel , it is under kernel hacking

```bash
[root@euler-hemanth tracing]# pwd
/sys/kernel/debug/tracing
[root@euler-hemanth tracing]# mount | grep ftrace
[root@euler-hemanth tracing]# mount | grep tracefs
tracefs on /sys/kernel/tracing type tracefs (rw,nosuid,nodev,noexec,relatime,seclabel)
tracefs on /sys/kernel/debug/tracing type tracefs (rw,nosuid,nodev,noexec,relatime,seclabel)
[root@euler-hemanth tracing]# cd /sys/kernel/tracing
[root@euler-hemanth tracing]# ls
available_events                  enabled_functions         options                set_event_pid           stack_trace_filter  trace_stat
available_filter_functions        error_log                 osnoise                set_ftrace_filter       synthetic_events    tracing_cpumask
available_filter_functions_addrs  events                    per_cpu                set_ftrace_notrace      timestamp_mode      tracing_max_latency
available_tracers                 free_buffer               printk_formats         set_ftrace_notrace_pid  touched_functions   tracing_on
buffer_percent                    function_profile_enabled  README                 set_ftrace_pid          trace               tracing_thresh
buffer_size_kb                    hwlat_detector            saved_cmdlines         set_graph_function      trace_clock         uprobe_events
buffer_total_size_kb              instances                 saved_cmdlines_size    set_graph_notrace       trace_marker        uprobe_profile
current_tracer                    kprobe_events             saved_tgids            snapshot                trace_marker_raw
dynamic_events                    kprobe_profile            set_event              stack_max_size          trace_options
dyn_ftrace_total_info             max_graph_depth           set_event_notrace_pid  stack_trace             trace_pipe
[root@euler-hemanth tracing]# cat tracing_on
1
[root@euler-hemanth tracing]# cat current_tracer
nop
[root@euler-hemanth tracing]# cat available_tracers
timerlat osnoise hwlat blk function_graph wakeup_dl wakeup_rt wakeup function nop
[root@euler-hemanth tracing]# echo 0 > tracing_on
[root@euler-hemanth tracing]# echo function > current_tracer
[root@euler-hemanth tracing]# echo 1 > tracing_on ; sleep 1 ; echo 0 > tracing_on
[root@euler-hemanth tracing]# ls -l trace
-rw-r-----. 1 root root 0 Dec 23 11:43 trace    //it is a sudo file, you need to copy the file into tem location.
cp trace /tmp/traceoutput
```
same like to show the function_graph
```bash
[root@euler-hemanth tracing]# echo function_graph > current_tracer
[root@euler-hemanth tracing]# echo 1 > tracing_on ; sleep 1 ; echo 0 > tracing_on
```
by default it shows only some minimal output only, there is some options to turn on under `/sys/kernel/tracing/options` 
```bash
[root@euler-hemanth options]# ls
annotate     context-info       funcgraph-cpu       funcgraph-retval      function-trace  markers          record-cmd   sym-userobj
bin          disable_on_free    funcgraph-duration  funcgraph-retval-hex  graph-time      overwrite        record-tgid  test_nop_accept
blk_cgname   display-graph      funcgraph-irqs      funcgraph-tail        hash-ptr        pause-on-trace   sleep-time   test_nop_refuse
blk_cgroup   event-fork         funcgraph-overhead  func-no-repeats       hex             printk-msg-only  stacktrace   trace_printk
blk_classic  fields             funcgraph-overrun   func_stack_trace      irq-info        print-parent     sym-addr     userstacktrace
block        funcgraph-abstime  funcgraph-proc      function-fork         latency-format  raw              sym-offset   verbose
```
for example output, check the [cheetsheet](https://github.com/SelamHemanth/Infobell_Training/blob/b75f07ee96586c89db9b6fe17954581bfccb4ee7/20-12-2024/Linux_Debugging/Infobellit_LinuxKernelDebugging_Dec2024_kaiwanTECH_3d/courseware/03_kernel_tracing/ftrace_cheatsheet-kaiwanTECH.pdf)

`Note:` There is a command which handles the tracer. 
        [trace-cmd](https://man7.org/linux/man-pages/man1/trace-cmd.1.html) - interacts with Ftrace Linux kernel internal tracer
```bash
sudo apt install trace-cmd
```
example usage:
```javascript
trace-cmd record -p function_graph -F /home/amd/a.out  //it will records the data
trace-cmd report ./trace.dat -l  //it will shows the output
