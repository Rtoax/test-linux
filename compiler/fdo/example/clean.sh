#!/bin/bash

clean()
{
	rm -f *.out *.gcda *.profraw *.profdata \
		perf.data* *.gcov "$@"
}

clean "$@"

