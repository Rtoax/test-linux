include python/sphinx.mk
include dir.mk

# Support more builder: singlehtml, etc.
.PHONY: htmldocs
htmldocs:
	${Q}${SHELL} ${TOPDIR}/scripts/docs/sphinx-build.sh
	$(call log_success, Startup HTTP server with $$ make serve)

.PHONY: serve
serve: htmldocs
	$(call log_success, Access: http://localhost:8888/)
	${Q}${SHELL} ${TOPDIR}/scripts/docs/sphinx-serve.sh
