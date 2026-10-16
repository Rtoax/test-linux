Namespace pid
=============

PID Namespace对进程PID重新标号，即不同的Namespace下的进程可以有同一个PID。

内核为所有的PID Namespace维护了一个树状结构，最顶层的是系统初始化创建的，被称为Root Namespace，由它创建的新的PID Namespace成为它的Child namespace，原先的PID Namespace成为新创建的Parent Namespace，这种情况下不同的PID Namespace形成一个等级体系：父节点可以看到子节点中的进程，可以通过信号对子节点的进程产生影响，反过来子节点无法看到父节点PID Namespace里面的进程。


- `pid_namespace(7)`
