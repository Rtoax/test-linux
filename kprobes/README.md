kprobe
======

```
  Kernel Space

│ Instruction 1 │                │ Instruction 1 │   ┌────▶│ Save context    │
│ Instruction 2 │                │ Instruction 2 │   │     │ Exec kprobe     │
│ Instruction 3 │                │ jmp ──────────┼───┘     │ Restore context │
│ Instruction 4 │ Inject kprobe  │ Instruction 4 │◀───┐    │ Instruction 3   │
│ Instruction 5 │ ─────────────▶ │ Instruction 5 │    └────┤ jmp             │
│ Instruction 6 │                │ Instruction 6 │         │                 │
│ ....          │                │ ....          │         │                 │
│               │                │               │         │                 │
│               │                │               │         │                 │
```
