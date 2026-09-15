#!/bin/bash

func1()
{
	echo $0 $1 $2

	nested_func2()
	{
		echo $0 $1 $2
	}

	nested_func2 n1 n2 n3
}

func1 f1 f2 f3

