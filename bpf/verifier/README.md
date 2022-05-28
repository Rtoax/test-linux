eBPF verifier
=============

* [https://www.kernel.org/doc/html/latest/bpf/verifier.html](https://www.kernel.org/doc/html/latest/bpf/verifier.html)

The safety of the eBPF program is determined in two steps.

* First step does DAG(Directed Acyclic Graph) check to disallow loops and other CFG validation. In particular it will detect programs that have unreachable instructions. (though classic BPF checker allows them)
* Second step starts from the first insn and descends all possible paths. It simulates execution of every insn and observes the state change of registers and stack.


