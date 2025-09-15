tmux - terminal multiplexer
===========================


 tmux new -s name      tmux attach -t name
┌────────────────┐     ┌────────────────┐
│$ ls            │     │$ ls            │
│                ├─────┤                │
│                │     │                │
└──────────────┬─┘     └────────────────┘
               │
               │       tmux attach -t name
               │       ┌────────────────┐
               └───────┤$ ls            │
                       │                │
                       │                │
                       └────────────────┘

 tmux kill-session -t name
