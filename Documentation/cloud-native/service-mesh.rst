============
Service Mesh
============

A service mesh is an infrastructure layer that gives applications capabilities
like zero-trust security, observability, and advanced traffic management,
without code changes.


.. toctree::
   :maxdepth: 1

   istio


Sidecar
-------

.. code-block:: text

         Microservice Pod
    ┌──────────────────────────┐
    │┌──────────┐ ┌──────────┐ │
    ││Service   │ │ Sidecar  │ │
    ││Container │ │ Container│ │
    │└──────────┘ └──────────┘ │
    └──────────────────────────┘


Links
-----

- https://istio.io/latest/about/service-mesh/
