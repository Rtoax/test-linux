#!/usr/bin/python
from bcc import BPF
print("Tracing... Hit Ctrl-C to end")
b = BPF(text="")
b.trace_print()
