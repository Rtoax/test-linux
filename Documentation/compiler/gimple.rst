GIMPLE
======

GIMPLE is a family of intermediate representations (IR) based on the tree data structure.

GIMPLE 是从 GENERIC 派生的三地址表示，它通过将 GENERIC 表达式分解为不超过 3 个操作数的元组（有一些例外，如函数调用）。

LTO
---

The C front end defines the following hooks which may affect interpretation of GIMPLE:

.. code-block:: text

    FINISH
    INIT_OPTIONS
    INITIALIZE_DIAGNOSTICS
    HANDLE_OPTION
    MISSING_ARGUMENT
    POST_OPTIONS
    GET_ALIAS_SET
    EXPAND_EXPR
    EXPAND_DECL
    MARK_ADDRESSABLE
    PARSE_FILE
    FINISH_INCOMPLETE_DECL
    REDUCE_BIT_FIELD_OPERATIONS
    NO_BODY_BLOCKS
    WARN_UNUSED_GLOBAL_DECL
    PRINT_IDENTIFIER TYPES_COMPATIBLE_P
    FUNCTION_ENTER_NESTED
    FUNCTION_LEAVE_NESTED
    FUNCTION_MISSING_NORETURN_OK_P
    DUP_LANG_SPECIFIC_DECL
    BUILTIN_FUNCTION
    COMMON_ATTRIBUTE_TABLE
    FORMAT_ATTRIBUTE_TABLE
    TREE_INLINING_CANNOT_INLINE_TREE_FN
    TREE_INLINING_DISREGARD_INLINE_LIMITS
    TREE_INLINING_CONVERT_PARM_FOR_INLINING
    TREE_DUMP_DUMP_TREE_FN
    CALLGRAPH_EXPAND_FUNCTION
    TYPE_FOR_MODE
    TYPE_FOR_SIZE
    SIGNED_TYPE
    SIGNED_OR_UNSIGNED_TYPE
    INCOMPLETE_TYPE_ERROR
    TYPE_PROMOTES_TO
    REGISTER_BUILTIN_TYPE
    TO_TARGET_CHARSET
    EXPR_TO_DECL
    GETDECLS
    WRITE_GLOBALS
    GIMPLIFY_EXPR
    OMP_PREDETERMINED_SHARING
    TREE_INLINING_VAR_MOD_TYPE_P
    NAME
    INIT

The C front end defines the following hooks which do not affect interpretation of GIMPLE:

* `IDENTIFIER_SIZE`:This hook is only use to compute the size to use when allocating an `IDENTIFIER_NODE`.
* `STATICP`: The only case handled by this hook is `COMPOUND_LITERAL_EXPR` which is eliminated during before GIMPLE.


Links
-----

* https://gcc.gnu.org/onlinedocs/gccint/GIMPLE.html
* https://gcc.gnu.org/wiki/LTO_Representation_Changes
