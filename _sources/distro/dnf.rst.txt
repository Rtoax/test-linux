RPM/DNF
=======

Spec
----

Scriptlets
~~~~~~~~~~

.. list-table::
   :widths: 15 15 15 15
   :header-rows: 1

   * - Scriptlet
     - Install
     - Upgrade
     - Uninstall
   * - %pretrans
     - $1 == 1
     - $1 == 2
     - N/A
   * - %pre
     - $1 == 1
     - $1 == 2
     - N/A
   * - %post
     - $1 == 1
     - $1 == 2
     - N/A
   * - %preun
     - N/A
     - $1 == 1
     - $1 == 0
   * - %postun
     - N/A
     - $1 == 1
     - $1 == 0
   * - %posttrans
     - $1 == 1
     - $1 == 2
     - N/A


Upgrade
-------

On upgrade, the scripts are run in the following order:

- `%pretrans` of new package
- `%pre` of new package
- (package install)
- `%post` of new package -- service currently started here
- `%triggerin` of other packages (set off by installing new package)
- `%triggerin` of new package (if any are true)
- `%triggerun` of old package (if it’s set off by uninstalling the old package)
- `%triggerun` of other packages (set off by uninstalling old package)
- `%preun` of old package
- (removal of old package)
- `%postun` of old package -- service currently stopped here
- `%triggerpostun` of old package (if it’s set off by uninstalling the old package)
- `%triggerpostun` of other packages (if they’re set off by uninstalling the old package)
- `%posttrans` of new package


Links
-----

- https://github.com/rpm-software-management/dnf
- https://github.com/rpm-software-management/dnf5.git
