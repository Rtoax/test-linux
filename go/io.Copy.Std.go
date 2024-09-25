package main

import (
	"io"
	"os"
	"sync"
)

func main() {
	var wg sync.WaitGroup
	wg.Add(1)
	io.Copy(os.Stdout, os.Stdin)
	wg.Done()
	wg.Wait()
}
