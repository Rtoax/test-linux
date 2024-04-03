
1.编译
	$ make 

2.加载
	$ sudo insmod chardev2.ko

3.创建节点
	3.1 查看创建的驱动
		$ grep chardev /proc/devices
	3.2 创建节点
		$ sudo mknod /dev/chardev2 c 231 0

4.使用节点
	见test.c

5.卸载驱动
	$ sudo rmmod chardev2

6.删除节点文件
	$ sudo rm /dev/chardev2


