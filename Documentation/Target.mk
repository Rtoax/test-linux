.PHONY: html
html:
	${Q}sphinx-build -M html . build
	$(call log_success, Startup HTTP server with $$ make serve)

.PHONY: serve
serve:
	$(call log_success, Access: http://localhost:8888/)
	${Q}python -m http.server 8888 --directory ./build/html/
