# break args	最常用的断点
# ------------------------------------------------------------
#	break main	函数中断点
#	break ChildClass::PrintMe	类中断点
#	break foo(int)		重载函数
#	break foo(int, int)	重载函数
#	break test.cc:foo(int) 源程序中的函数
#	break 11	第11行断点
#	break test.cc:11	test.cc 的 11 行
#	break +12	执行到某一行，在这一行的附近设置断点
#	break -10
#	break *0x80485ba	在某个内存地址中设置断点
#
#	info breakpoints	查看断点
#	-------------------------------------------------------
#		(gdb) info breakpoints
#		Num     Type           Disp Enb Address            What
#		1       breakpoint     keep y   0x000000000040053c in main at test.c:7
#
#	enable	<breakpoint number>	开启断点
#	disable <breakpoint number>	关闭断点
#
#	enable delete <brk num>	启动断点，但是一旦在断点处暂停，就删除断点
#	enable once <brk num>	只启动一起，暂停后就关闭
#
#	break <args> if <condition>	条件断点：设置断点的同时就设置断点的条件
#	condition <brk num> <condition> 条件断点：对一个一直断点设置条件
#
#	delete breakpoints <brk num>	删除一个或所有断点
break hello
break main
info breakpoints
# hello()
enable 1
enable once 1
enable delete 1
# main()
disable 2
delete breakpoints 2
run
set $addr = &main
break *$addr
continue
quit
