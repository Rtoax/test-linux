
dtb-y := helloworld.dtb

all:
	#make -C /lib/modules/$(shell uname -r)/build/ M=${PWD}
	dtc -I dts -O dtb -o helloworld.dtb helloworld.dts

clean:
	#make -C /lib/modules/$(shell uname -r)/build/ M=${PWD} clean
