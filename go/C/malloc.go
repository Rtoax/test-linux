package main

/*
#include <stdlib.h>
*/
import "C"
import (
	"fmt"
)

func main() {
	size := C.size_t(16)
	ptr := C.malloc(size)
	if ptr == nil {
		fmt.Println("malloc failed")
		return
	}
	defer C.free(ptr)
}
