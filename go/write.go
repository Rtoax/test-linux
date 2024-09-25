package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {

	filePath := "write.txt"
	file, err := os.OpenFile(filePath, os.O_WRONLY|os.O_APPEND|os.O_CREATE, 0666)
	if err != nil {
		fmt.Println("Open failed", err)
	}
	defer file.Close()

	write := bufio.NewWriter(file)

	for i := 0; i < 5; i++ {
		write.WriteString("Hello\n")
	}
	write.Flush()
}
