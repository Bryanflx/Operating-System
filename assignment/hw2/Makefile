obj-m += helloworld.o
kerneldir := /lib/modules/5.4.0-48-generic/build
PWD := $(shell pwd)

all:
		make -C $(kerneldir) M=$(PWD) modules
		
clean:
		make -C $(kerneldir) M=$(PWD) clean
