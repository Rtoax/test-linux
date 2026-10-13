# The CDAT provides functional and performance attributes of devices such as CXL
# accelerators, switches, or endpoints. The table formatting is similar to ACPI
# tables. CDAT data may be parsed by BIOS at boot or may be enumerated at
# runtime (after device hotplug, for example).
#
# commit 1deed101cac2 ("cxl: add CDAT (Coherent Device Attribute Table)")
#
# Refs:
# - https://docs.kernel.org/driver-api/cxl/platform/cdat.html
prog-y += endpoint.sh
