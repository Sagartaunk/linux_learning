KDIR ?= $(HOME)/Documents/linux
LLVM ?= 1

all:
	$(MAKE) -C $(KDIR) M=$(CURDIR) LLVM=$(LLVM) modules

clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) LLVM=$(LLVM) clean
