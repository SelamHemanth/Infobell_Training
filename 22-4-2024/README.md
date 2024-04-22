#Kernel Internels
---
***Linux Architecture***
---
	$ ps aux | less   -> It shows the kernel threads
	$ flamegraph      -> It shows the flame graphs for visual stackcd 
 * eBPF is a virtual machine technology allowing one to write a program in userspace and run it within the kernel.
 * Linux Kernel Mailing List (LKML) -> It tracks the kernel changes https://lwn.net/Kernel/ 

***Kernel Soruce Tree***
---
 * The stable kernel verison are releases for 20 sublevel versions
---
	$ uname -r
		6.8.7-50-generic 
			* 6          -> Manjor version
			* 8          -> minor version
			* 7  	     -> patch version
			* 50-generic -> destro version 	
 * Linux kernel kernel finger banner shows the all of LTS and release candidate versions
	$ curl -L https://www.kernel.org/finger_banner
		The latest stable version of the Linux kernel is:             6.8.7
		The latest mainline version of the Linux kernel is:           6.9-rc5
		The latest stable 6.8 version of the Linux kernel is:         6.8.7
		The latest stable 6.7 version of the Linux kernel is:         6.7.12 (EOL)
		The latest longterm 6.6 version of the Linux kernel is:       6.6.28
		The latest longterm 6.1 version of the Linux kernel is:       6.1.87
		The latest longterm 5.15 version of the Linux kernel is:      5.15.156
		The latest longterm 5.10 version of the Linux kernel is:      5.10.215
		The latest longterm 5.4 version of the Linux kernel is:       5.4.274
		The latest longterm 4.19 version of the Linux kernel is:      4.19.312
		The latest linux-next version of the Linux kernel is:         next-20240422

***Kernel Source Code***
---

	The linux kernel soruce code contails all the following files

arch/    CREDITS         fs/       Kbuild   LICENSES/    modules.builtin          net/      security/   usr/
block/   crypto/         include/  Kconfig  MAINTAINERS  modules.builtin.modinfo  README    sound/      virt/
certs/   Documentation/  init/     kernel/  Makefile     modules.order            samples/  System.map  vmlinux*
COPYING  drivers/        ipc/      lib/     mm/          Module.symvers           scripts/  tools/      vmlinux.o

 * COPYING    -> It contains the licence
 * CREDITS    -> It contains the contributers details
 * init       -> It contains the initial BIOS code i.e., start_kernel
 * arch       -> It contains the all supported architecture code
 * kernel     -> It contains the kernel source code
 * fs         -> It contains the all of the file system source code
 * net        -> It contains the network related source code
 * ipc        -> It contains the all of inter process communication
 * lib        -> It contains the librarries
 * scripts    -> It contains the all the shell scripts
 * security   -> It contains the additional security models
 * sound      -> It contains the sound related source code
 * tools      -> It contains the all the tools (perf, vim ,etc.,.)
 * virt       -> It contains the virtualization source code like KVM (kernel vertul machine)
 * include    -> It contains the all the header files
 * drivers    -> It contains the all device drivers 
 * MAINTAINERS-> It contains the all of maintainers inmformation

***Build Kernel***
---

 * Download kernel source code using this link
---
	$ wget  https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.1.87.tar.xz
 * Extract the tarbal
--- 
	$ tar -xvf <tar file>
 * Install required packages
---
	$ sudo apt update
	$ sudo apt install -y gcc make perl
	$ sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison
 * Configure the souce code before installing the kernel
---
	$ make menuconfig  or make qconfig   or make xconfig
---
 **Note**: By default it compile for X86-Arch . If you want to compile for other architectures. Use this option
		$ make ARCH=./arch/<type of arch>
       Optional steps to remove some errors
  		scripts/config --disable SYSTEM_TRUSTED_KEYS
  		scripts/config --disable SYSTEM_REVOCATION_KEYS
  		scripts/config --disable  CONFIG_DEBUG_INFO_BTF
  		scripts/config --disable NET_VENDOR_NETRONOME
 * Now you have full configuration for build the kernel
---
	$ make -j<number CPU>
 
 
