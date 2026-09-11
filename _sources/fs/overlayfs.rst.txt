overlayfs
=========

mnt namespace not isolate physic file system, some processes still modify this
file in physical file system.

Overlayfs use Copy On Write.


FAQ
---

- Q: Why can I see the /tmp directory in the container(merged overlay), but get
     an error -ENOENT when trying to write to this directory?
- A: OverlayFS officially requires that after mounting, you must not bypass the
     merged mount point and directly modify the actual content of
     lowerdir/upperdir. Otherwise, undefined behavior will occur where the cache
     is inconsistent with the actual content. This is the scenario most likely
     to trigger this problem.

.. code-block:: bash

    # 启动容器
    $ sudo podman run --rm -ti --name master15 image.cestc.cn/release/cclinux2209:22.09.2-master-15-1 bash

    # 查看容器的overlayfs（也可以使用crictl）
    $ sudo podman inspect master15 --format "{{ .GraphDriver.Data.UpperDir }}"
    # 显示内容类似：
    # /var/lib/containers/storage/overlay/8077007dd7c71798ad4b051b3984bdb42770ab4ce5ebb6358cb30e9822e34739/diff

    # 在 HostOS 中，进入 UpperDir 目录，并查看：
    cd /var/lib/containers/storage/overlay/8077007dd7c71798ad4b051b3984bdb42770ab4ce5ebb6358cb30e9822e34739/diff/
    ls
    # 显示内容可能为
    # run

    # 在容器中创建 /tmp/a1 文件(创建成功)
    # PS： 此时 overlayfs 发生copy-up，将LowerDir中的/tmp 拷贝到 UpperDir中的 /tmp中
    touch /tmp/a1

    # 此时，在Host中的 UpperDir中，可以看到/tmp被创建
    ls
    # 显示如下（tmp是新创建的，拥有新的inode号）
    # run  tmp

    # 此时，强制删除 UpperDir 中的 tmp 目录。
    rm -fr tmp/

    # 然后，在容器中，无法在 /tmp 创建任何文件，但是可以看到目录 /tmp：
    ls
    # ... sys  tmp  usr  var

    touch /tmp/xyz
    # touch: cannot touch '/tmp/xyz': No such file or directory

    # Recover: drop dentry cache
    echo 2 | sudo tee /proc/sys/vm/drop_caches
