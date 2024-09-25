package main

import (
	"fmt"
	"io"
	"os"
)

func main() {
	srcFile, err := os.Open("/etc/os-release")
	check(err)
	defer srcFile.Close()

	/* creates if file doesn't exist */
	destFile, err := os.Create("os-release")
	check(err)
	defer destFile.Close()

	/* check first var for number of bytes copied */
	_, err = io.Copy(destFile, srcFile)
	check(err)

	err = destFile.Sync()
	check(err)
}

func check(err error) {
	if err != nil {
		fmt.Println("Error : %s", err.Error())
		os.Exit(1)
	}
}
