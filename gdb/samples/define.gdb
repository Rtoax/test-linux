define add
	echo $arg0 + $arg1\n
	set $sum = $arg0 + $arg1
	printf "sum = %d\n", $sum
end
define mybacktrace
	backtrace
end
add 3 7
break hello
run
mybacktrace
continue
quit
