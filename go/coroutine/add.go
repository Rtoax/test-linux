package main

import (
	"fmt"
	"time"
)

func Add(x, y int) {
	z := x + y
	fmt.Println(z)
}

func main() {
	for i := 0; i < 10; i++ {
		go Add(i, i)
	}
	/* Must give gocoroutine some times to finish */
	time.Sleep(1000 * time.Millisecond)
}
