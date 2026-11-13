.. SPDX-License-Identifier: GPL-2.0

===================
Test Linux Template
===================

Test Linux template is Makefile template, including serial of **.mk** Makefiles.
Those Makefile could be included in **Build.mk**, **Target.mk**.

For example **Build.mk**:

.. code-block:: Makefile

  include arch.mk

  $(info CPU_ARCH = ${CPU_ARCH})
