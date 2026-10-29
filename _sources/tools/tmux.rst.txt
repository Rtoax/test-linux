tmux - terminal multiplexer
===========================

.. code-block:: text

      $ tmux new -s name         $ tmux attach -t name
    ┌─────────────────────┐     ┌─────────────────────┐
    │  $ ls               │     │$ ls                 │
    │                     ├─────┤                     │
    │                     │     │                     │
    └──────────────────┬──┘     └─────────────────────┘
                       │
                       │         $ tmux attach -t name
                       │        ┌─────────────────────┐
                       └────────┤$ ls                 │
                                │                     │
                                │$ tmux detach-client │
                                └─────────────────────┘

.. code-block:: bash

    $ tmux ls
    $ tmux kill-session -t name
