.. SPDX-License-Identifier: GPL-2.0

===========
Quick Start
===========

The purpose of this document is to compile the code of this directory and
subdirectories directly in each level of directory.


Install depends
---------------

.. code-block:: bash

        $ sudo make deps


Config
------

.. code-block:: bash

        $ make config


Install and Uninstall
---------------------

.. code-block:: bash

        $ sudo make install
        $ sudo make uninstall


Compile in Top Directory
------------------------

You'd better compiled under git-repo, because some Makefile use **git rev-parse
--show-toplevel** get top-dir.

.. code-block:: bash

        $ make build

Compile without kernel modules:

.. code-block:: bash

        $ make build KMOD=0

Compile with **-m32**:

.. code-block:: bash

        $ make build M32=1

Compile with verbose:

.. code-block:: bash

        $ make build V=1

Stop immediately when an error occurs:

.. code-block:: bash

        $ make build CHECK_ERROR=1

