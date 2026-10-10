git lfs
=======

1. 创建一个新的 lfs 仓库

.. code-block:: shell

  git lfs install

2. 添加需要 lfs 管理的文件类型

.. code-block:: shell

  git lfs track "*.tar.xz"


3. 添加 lfs 追踪文件

.. code-block:: shell

  git add .gitattributes
  git add --all


4. 查看 lfs 大文件

.. code-block:: shell

  git lfs ls-files


5. 提交

.. code-block:: shell

  git push
