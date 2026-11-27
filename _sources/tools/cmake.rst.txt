CMake
=====

CMake Modules
-------------

Store extra cmake modules, see also `/usr/share/cmake/Modules`.

Usage
~~~~~

.. code-block:: cmake

    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
    # Or
    list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")
