# module-params

sudo insmod ./params-test0.ko irq=2 debug=0640 devname=rtoax num=11

sudo cat /sys/module/params_test0/parameters/devname
sudo cat /sys/module/params_test0/parameters/irqtype
sudo cat /sys/module/params_test0/parameters/irq
