package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Println("main")
	/* 1s */
	time.Sleep(1000 * time.Millisecond)
	fmt.Println("main done")
}
