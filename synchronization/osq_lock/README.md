OSQ Lock - Optimistic Spin Queue
================================

MCS 锁机制的一个实现。

```
                 +------+            +------+         +------+
                 | CPU0 |            | CPU1 |         | CPUN |
              +--+------+--+      +--+------+--+ ...+-+------+--+
       Init:  |  locked=0  |      |  locked=0  |    | locked=0  |
              |  cpu=1     |      |  cpu=2     |    | cpu=N+1   |
      tail=0  |  prev=NULL |      |  prev=NULL |    | prev=NULL |
              |  next=NULL |      |  next=NULL |    | next=NULL |
              +------------+      +------------+    +-----------+
+---------------------------------------------------------------+   +
  CPU0         old tail=0                                           |
 osq_lock:     tail=cpu=1                                           |
+---------------------------------------------------------------+   |
  CPU1                             old tail=1                       |
                                   tail=2                           |
 osq_lock:                         prev=CPU0                        |
               next=CPU1                                            |
                                   for (;;) {                       v
                                     ##atomic load##              time
                                     if (locked==1)
                                       return true;
                                     cpu_relax();
                                     ##update prev##
                                   }
+---------------------------------------------------------------+
  CPU0         ##atomic cas##
osq_unlock:    if (tail==1) {
                 tail=0;
                 return;
               }
              +if (next) {
              |  ##atomic store##
              |  next->locked=1
              |  next=NULL
              |                    for (;;) {
              |                      ##atomic load##
              |                      if (locked==1)
              |                        return true;##CPU1 GET Lock##
              |                    }
              +} else {
                 TODO
 +---------------------------------------------------------------+
   CPU1                            ##atomic cas##
 osq_unlock:                       if (tail==2) {
                                     tail=0;
                                     return;
                                   }
```
