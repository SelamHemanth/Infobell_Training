# Simplest LKM Makefile
MODNAME = ass-4

obj-m	:= $(MODNAME).o

KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

all: module

module:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
install:
	sudo $(MAKE) -C $(KDIR) M=$(PWD) modules_install
	sudo depmod
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
