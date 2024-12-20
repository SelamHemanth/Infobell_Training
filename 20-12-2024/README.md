# Linux Kernel Debugging
---

***Topics***
---
1. Trace Printk
2.  Dynamic Printkcd ar  
3.  Debugfs
4.  Tools (Trace, FTrace, LTTng, TraceCompass, Kernelshark, KGDB)
5.  Kernel Oops
6.  Kprobes
7.  Perf-tools
8.  Kernel Memory Debugging (KASAN)

***Pre-Requirments***
--- 
* Download [linux kernel](https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git) source code and configure
* Install reqired packages to build
```bash
# Debian:
sudo apt-get install git make fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison
# RHEL:
sudo yum install bc gcc git vim time gcc-c++ kernel-devel perl make numactl openssl openssl-devel libmpc mpfr ncurses-devel bison tar rsync libstdc++-devel libtool bison flex zlib zlib-devel elfutils-libelf-devel ncurses-devel createrepo rpm-build rpmdevtools -y
```  

***Steps to debug***
---
* Collect modules and configure kernel
```bash
lsmod > /tmp/mylsmod
make LSMOD=/tmp/mylsmod localmodconfig
make menuconfig
```
* Enable following configurations
```javascript
* General setup > Local version - append to kernel release
                > <*> Kernel .config support
                > [*]   Enable access to .config through /proc/config.gz
                > [*]   Configure standard kernel features (expert users)
* Kernel hacking > printk and dmesg options > [*] Show timing information on printks
                                            > [*] Verbose BUG() reporting (adds 70K)
                 > -*- Kernel debugging
                 > Compile-time checks and compiler options  > [*] Provide GDB scripts for kernel debugging
                                                             > [*] Compile-time stack metadata validation
                                                             > (1500) Warn for stack frames larger than (optional, if you got frame size error , increase the size upto 8kb)
                 > Memory Debugging  >  [*] Enable SLUB debugging support
                                     >  [*] Kernel memory leak detector
                                     >  [*]   Default kmemleak to off
                                     >  [*] KASAN: dynamic memory safety error detector >  [*]   Check accesses to vmalloc allocations
                                                                                        >  <M>   KUnit-incompatible tests of KASAN bug detection capabilities
                 > Lock Debugging (spinlocks, mutexes, etc...)  >  [*] Lock debugging: prove locking correctness
                                                                >  [*] Sleep inside atomic section checking
                 > [*] Tracers > [*]     Kernel Function Graph Tracer
                               > [*]       Kernel Function Graph Return Value
```
* save and exit form menuconfig
* Build the kernel
```bash
make -j32
```
* Install modules
```bash
sudo make modules_install
```
* Install the kernel
```bash
sudo make install
```
* Update grub and reboot
```bash
sudo reboot
```



