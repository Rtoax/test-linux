task
====

.. code-block:: text

    crash> task 1
    PID: 1      TASK: ffff7000019c0000  CPU: 21  COMMAND: "systemd"
    struct task_struct {
      thread_info = {
        flags = 1024,
        {
          preempt_count = 4295032832,
          preempt = {
            count = 65536,
            need_resched = 1
          }
        }
      },
      ...
