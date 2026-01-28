Template of Test-Linux
======================

Store all mk files of test-linux.

In the test-linux project, all Makefiles in the template directory have the `.mk` extension. The `.mk` extension cannot be used in other directories.


# Syntax

If you want to check if a feature or software exists, you need to set `HAVE_` to either `n` or `y`, for example, in **cuda.mk** define `HAVE_CUDA=y` if cuda was installed in your system.

`HAVE_` cannot be empty. For example, you cannot use `ifdef HAVE_CUDA` to determine whether CUDA is installed.
