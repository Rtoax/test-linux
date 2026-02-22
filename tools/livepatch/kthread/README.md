Discription: module/driver kthread livepatch demo
Author:	Rong Tao <rtoax@foxmail.com>
Time:	2021.11.03

# Procedures

1. make
2. sudo insmod kthread.ko 
3. watch -n1 "dmesg tail"
4. sudo insmod patchkthread.ko 
	# now, you'll see `MyKthread count xxx` turns to `MyKthread count xxx, patched`
5. echo 0 > /sys/kernel/livepatch/patchkthread/enabled
	# now, you'll see `MyKthread count xxx, patched` turns to `MyKthread count xxx`
6. sudo rmmod patchkthread
7. sudo rmmod kthread.ko
