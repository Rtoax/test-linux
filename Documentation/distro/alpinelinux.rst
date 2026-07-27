Alpine Linux
============

Alpine Linux is a security-oriented, lightweight Linux distribution based on
musl libc and busybox.


Install from ISO
----------------

.. code-block:: shell

   localhost:~# setup-alpine
   Enter system hostname (fully qualified form, e.g. 'foo.example.org') [localhost] alpine

   按照提示完成配置...

   Creating file systems...
   Installing system on /dev/vda3:
   /mnt/boot is device /dev/vda1
    22% ██████████

   最后，进行漫长等待...

   100% ████████████████████████████████████████████
   creating /boot/initramfs-lts for 6.18.39-0-lts
   /boot is device /dev/vda1
   alphine:~#

   最后重启...

   alphine:~# reboot


Config Source
-------------

.. code-block:: shell

   $ vi /etc/apk/repositories
   # Example:
   https://mirrors.tuna.tsinghua.edu.cn/alpine/v3.24/main
   https://mirrors.tuna.tsinghua.edu.cn/alpine/v3.24/community

   $ apk update


Install Base PKGs
-----------------

.. code-block:: shell

   $ apk add coreutils git util-linux findutils grep less bash pciutils \
             vim usbutils make gcc jq ncurses musl-dev


Install Desktop
---------------

.. code-block:: shell

   $ setup-desktop
   Which desktop environment? ('gnome', 'plasma', 'xfce', 'mate', 'sway', 'lxqt' or 'none') [none] mate

   # Then:
   $ reboot


Links
-----

- https://www.alpinelinux.org/about/
- https://mirrors.tuna.tsinghua.edu.cn/alpine/
