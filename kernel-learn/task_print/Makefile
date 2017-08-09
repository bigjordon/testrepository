ifneq ($(KERNELRELEASE),)
 $(warning go here)
 obj-m:=readprocess.o
else
 $(warning do go here)
 KDIR:= /lib/modules/$(shell uname -r)/build
 PWD:= $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules   
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
endif
