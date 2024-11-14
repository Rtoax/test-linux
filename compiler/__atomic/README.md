Compiler __atomic
=================

The following built-in functions approximately match the requirements for the C++11 memory model. They are all identified by being prefixed with `__atomic` and most are overloaded so that they work with multiple types.

These functions are intended to replace the legacy `__sync` builtins. The main difference is that the memory order that is requested is a parameter to the functions. New code should always use the `__atomic` builtins rather than the `__sync` builtins.


# Memory Order

- `__ATOMIC_RELAXED`: Implies no inter-thread ordering constraints.
	* 意味着没有线程间排序约束。

- `__ATOMIC_CONSUME`: This is currently implemented using the stronger `__ATOMIC_ACQUIRE` memory order because of a deficiency in C++11’s semantics for `memory_order_consume`.
	* `__ATOMIC_ACQUIRE` 由于 C++11 的语义存在缺陷，目前使用更强的内存顺序来实现`memory_order_consume`

- `__ATOMIC_ACQUIRE`: Creates an inter-thread happens-before constraint from the release (or stronger) semantic store to this acquire load. Can prevent hoisting of code to before the operation.
	* 可以防止将代码提升到操作之前。
	* load barrier

- `__ATOMIC_RELEASE`: Creates an inter-thread happens-before constraint to acquire (or stronger) semantic loads that read from this release store. Can prevent sinking of code to after the operation.
	* 可以防止代码沉入操作之后。
	* store barrier

- `__ATOMIC_ACQ_REL`: Combines the effects of both `__ATOMIC_ACQUIRE` and `__ATOMIC_RELEASE`.
	* `__ATOMIC_ACQUIRE`和`__ATOMIC_RELEASE`结合。
	* store-load barrier
	* 在`aarch64`上是**读写屏障**

- `__ATOMIC_SEQ_CST`: Enforces total ordering with all other `__ATOMIC_SEQ_CST` operations.
	* 强制对所有其他操作进行总排序`__ATOMIC_SEQ_CST`。
	* **读写屏障**


# Links

- https://gcc.gnu.org/onlinedocs/gcc-14.2.0/gcc/_005f_005fatomic-Builtins.html

