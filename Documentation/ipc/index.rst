================================
IPC - InterProcess Communication
================================

.. toctree::
   :maxdepth: 1

   abbrev


Generating IPC identifiers from IPC Keys

.. code-block:: text

     char *pathname
    ----------------> ftok() -\
        int id                 \
                                \|
                                msgget()  int identifier  msgctl(),msgend(),msgrcv()
                                semget()  --------------> semctl(),semop()
    --------------------------> shmget()                  shmctl(),shmat(),shmdt()
      key of IPC_PRIVATE      Open or create                  Access IPC channel
                                IPC channel


.. toctree::
   :maxdepth: 1

   pipe
   shm
   msgqueue
   dbus


Links
-----

- https://github.com/unpbook/unpv13e
