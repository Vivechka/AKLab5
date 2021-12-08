ifneq ($(KERNELRELEASE),)

obj-m +=  hello1.o
obj-m +=  hello2.o
EXTRA_CFLAGS := -I$(src)/inc

else

KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -I$PWD/inc -C $(KDIR) M=$$PWD
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif