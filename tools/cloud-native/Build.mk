include k8s.mk
include grafana.mk
include prometheus.mk

subdir-${HAVE_K8S} += kubernetes
subdir-${HAVE_GRAFANA} += grafana
subdir-${HAVE_PROMETHEUS} += prometheus
