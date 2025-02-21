
obj-m += bio_init.o

all:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	@echo >/dev/null

clean:
	${Q}make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
