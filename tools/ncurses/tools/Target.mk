# This file be used in test-linux, unuseful in github.com/rtoax/plotcake
#
# Examples need to depends on plotcake, make sure re-run if plotcake
# re-compiled.
${OUTPUT}examples.sh.prog.log: plotcake
${OUTPUT}examples.exp.prog.log: plotcake

build/plotcake: CMakeLists.txt
	${Q}mkdir -p build
	${Q}cmake -B build .
	${Q}make -C build
	${Q}sudo make -C build install
