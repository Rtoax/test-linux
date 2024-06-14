IPC - 进程间通信
==================

Generating IPC identifiers from IPC Keys

```
 char *pathname
----------------> ftok() -\
    int id                 \
                            \|
                            msgget()  int identifier  msgctl(),msgend(),msgrcv()
                            semget()  --------------> semctl(),semop()
--------------------------> shmget()                  shmctl(),shmat(),shmdt()
  key of IPC_PRIVATE      Open or create                  Access IPC channel
                            IPC channel
```


# Links

- https://github.com/unpbook/unpv13e

