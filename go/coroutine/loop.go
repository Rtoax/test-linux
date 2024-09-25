package main

import (
	"fmt"
	"time"
)

func Loop() {
	for i := 0;; i++ {
		time.Sleep(2000)
		fmt.Println("loop", i)
	}
}

func main() {
	go Loop()
	fmt.Println("main")
	/* 1s */
	time.Sleep(1000 * time.Millisecond)
}
