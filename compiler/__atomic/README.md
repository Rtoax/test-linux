Compiler __atomic
=================

The following built-in functions approximately match the requirements for the C++11 memory model. They are all identified by being prefixed with `__atomic` and most are overloaded so that they work with multiple types.

These functions are intended to replace the legacy `__sync` builtins. The main difference is that the memory order that is requested is a parameter to the functions. New code should always use the `__atomic` builtins rather than the `__sync` builtins.


# Links

- https://gcc.gnu.org/onlinedocs/gcc-14.2.0/gcc/_005f_005fatomic-Builtins.html

