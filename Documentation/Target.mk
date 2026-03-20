include python/sphinx.mk

.PHONY: htmldocs
htmldocs:
	${Q}${SPHINX_BUILD} -M html . build --fail-on-warning
	$(call log_success, Startup HTTP server with $$ make serve)

.PHONY: serve
serve: htmldocs
	$(call log_success, Access: http://localhost:8888/)
	${Q}python -m http.server 8888 --directory ./build/html/
