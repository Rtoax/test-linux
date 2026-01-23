# SPDX-License-Identifier: GPL-3.0

$(info PHONY = ${PHONY})
$(info $$? = $?)

# .PHONY: Declaring all is a "pseudo-target" rather than an actual file.
.PHONY: build
build:
