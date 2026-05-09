#!/bin/bash
set -e

kargs() {
	rpm-ostree kargs --delete=intel_iommu=on
}
