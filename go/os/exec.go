package main

import (
	"fmt"
	"os"
	"os/exec"
)

func main() {
	var cmd *exec.Cmd

	cmd = exec.Command("ls", "-al")

	err := cmd.Run()
	if err != nil {
		fmt.Println("Error:", err)
		os.Exit(1)
	}
	fmt.Println("Shutdown command executed successfully.")
}
