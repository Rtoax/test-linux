.. SPDX-License-Identifier: GPL-2.0

======================
Test Linux Quick Start
======================

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

    $ make build KMOD=

Compile without user space code:

.. code-block:: bash

    $ make build USRC=

Compile with **32bits mathine**:

.. code-block:: bash

    $ make build M32=1

Compile with verbose:

.. code-block:: bash

    $ make build V=1

Stop immediately when an error occurs:

.. code-block:: bash

    $ make build ERROR_ABORT=1

Compile without subdirectories:

.. code-block:: bash

    $ make build NOSUBDIR=1
