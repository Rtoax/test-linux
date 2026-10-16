============
Service Mesh
============

A service mesh is an infrastructure layer that gives applications capabilities
like zero-trust security, observability, and advanced traffic management,
without code changes.


.. toctree::
   :maxdepth: 1

   istio
   envoy


Sidecar
-------

.. code-block:: text

            Microservice Pod
   ┌────────────────────────────────────┐
   │┌──────────┐          ┌───────────┐ │Ingress
   ││          │  UNIX    │ (Envoy)   │◀┼────────
   ││ Service  │  Socket  │ Sidecar   │ │
   ││ Container│◀────────▶│ Container │ │Egress
   ││          │          │           │─┼───────▶
   │└──────────┘          └───────────┘ │
   └────────────────────────────────────┘


Envoy: Service Proxy
~~~~~~~~~~~~~~~~~~~~

Envoy is an L7 proxy and communication bus designed for large modern service
oriented architectures.


Links
-----

- https://www.envoyproxy.io/
- https://istio.io/latest/about/service-mesh/
