Signal
======

信号
----

SIGINT
~~~~~~

程序终止(interrupt)信号, 在用户键入INTR字符(通常是Ctrl-C)
时发出，用于通知前台进程组终止进程

SIGQUIT
~~~~~~~

和SIGINT类似, 但由QUIT字符(通常是Ctrl-\)来控制. 进程在因收到SIGQUIT退出时会产生core文件,
在这个意义上类似于一个程序错误信号。

SIGSTOP
~~~~~~~

停止(stopped)进程的执行. 注意它和terminate以及interrupt的区别:该进程还未结束,
只是暂停执行. 本信号不能被阻塞, 处理或忽略.

SIGTERM
~~~~~~~

程序结束(terminate)信号,
与SIGKILL不同的是该信号可以被阻塞和处理。通常用来要求程序自己正常退出，
shell命令kill缺省产生这个信号。如果进程终止不了，我们才会尝试SIGKILL。

More
~~~~

.. list-table::
   :header-rows: 1

   * - Signal
     - Description
   * - SIGHUP
     - 终止进程 终端线路挂断
   * - SIGINT
     - 终止进程 中断进程
   * - SIGQUIT
     - 建立baiCORE文件终止进程，并且生成core文件
   * - SIGILL
     - 建立CORE文件 非法指令
   * - SIGTRAP
     - 建立CORE文件 跟踪自陷
   * - SIGBUS
     - 建立CORE文件 总线错误
   * - SIGSEGV
     - 建立CORE文件 段非法错误
   * - SIGFPE
     - 建立CORE文件 浮点异常
   * - SIGIOT
     - 建立CORE文件 执行I/O自陷
   * - SIGKILL
     - 终止进程 杀死进程
   * - SIGPIPE
     - 终止进程 向一个没有读进程的管道写数据
   * - SIGALARM
     - 终止进程 计时器到时
   * - SIGTERM
     - 终止进程 软件终止信号
   * - SIGSTOP
     - 停止进程 非终端来的停止信号
   * - SIGTSTP
     - 停止进程 终端来的停止信号
   * - SIGCONT
     - 忽略信号 继续执行一个停止的进程
   * - SIGURG
     - 忽略信号 I/O紧急信号
   * - SIGIO
     - 忽略信号 描述符上可以进行I/O
   * - SIGCHLD
     - 忽略信号 当子进程停止或退出时通知父进程
   * - SIGTTOU
     - 停止进程 后台进程写终端
   * - SIGTTIN
     - 停止进程 后台进程读终端
   * - SIGXGPU
     - 终止进程 CPU时限超时
   * - SIGXFSZ
     - 终止进程 文件长度过长
   * - SIGWINCH
     - 忽略信号 窗口大小发生变化
   * - SIGPROF
     - 终止进程 统计分布图用计时器到时
   * - SIGUSR1
     - 终止进程 用户定义信号1
   * - SIGUSR2
     - 终止进程 用户定义信号2
   * - SIGVTALRM
     - 终止进程 虚拟计时器到时
