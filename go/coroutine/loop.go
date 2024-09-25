package main

import (
	"fmt"
	"time"
)

func Loop() {
	for i := 0;; i++ {
		time.Sleep(1000 * time.Millisecond)
		fmt.Println("loop", i)
	}
}

func main() {
	go Loop()
	fmt.Println("main")
	/* 5s */
	time.Sleep(5000 * time.Millisecond)
}
