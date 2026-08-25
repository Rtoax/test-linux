include python/sphinx.mk
include dir.mk

# Support more builder: singlehtml, etc.
.PHONY: htmldocs
htmldocs:
	$(call log_success, Start htmldocs building)
	${Q}${SHELL} ${TOPDIR}/scripts/docs/sphinx-build.sh
	$(call log_success, Startup HTTP server with $$ make serve)

.PHONY: serve
serve: htmldocs
	$(call log_success, --------------------------------------------------)
	${Q}${SHELL} ${TOPDIR}/scripts/docs/sphinx-serve.sh
