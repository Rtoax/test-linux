.PHONY: build0
build0:
	${Q}mkdir -p build && pushd build && cmake .. && make && popd

.PHONY: clean0
clean0:
	${Q}rm -rf build
