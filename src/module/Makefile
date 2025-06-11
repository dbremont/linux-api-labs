obj-m := hello.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm  -f *.o *.ko *.mod.c *.symvers *.order
	find . -maxdepth 1 -type f -name ".*" -exec rm {} \;