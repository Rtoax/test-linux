post-foo:
	${Q}./foo
	${Q}gprof ./foo gmon.out | gprof2dot > foo.dot
	${Q}dot -Tpng foo.dot -o foo.png
	${Q}dot -Tsvg foo.dot -o foo.svg

clean-foo:
	${Q}rm -f *.dot *.png *.svg
