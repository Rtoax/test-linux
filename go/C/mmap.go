package main

/*
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
*/
import "C"

import (
	"fmt"
	"os"
	"unsafe"
)

func main() {
	file, err := os.OpenFile("test.dat", os.O_RDWR|os.O_CREATE, 0644)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	const size = 4096
	err = file.Truncate(size)
	if err != nil {
		panic(err)
	}

	fd := file.Fd()

	data := C.mmap(
		nil,
		C.size_t(size),
		C.PROT_READ|C.PROT_WRITE,
		C.MAP_SHARED,
		C.int(fd),
		0,
	)

	if data == unsafe.Pointer(uintptr(C.MAP_FAILED)) {
		panic("mmap failed")
	}
	defer C.munmap(data, C.size_t(size))

	arr := (*[size]byte)(data)

	arr[0] = 42
	fmt.Println("Write ok, arr[0] =", arr[0])
}
