/* For test Golang Docker file
 *
 * Command Line:
 * $ sudo docker run --rm -v ${PWD}:/srv/ 43bd173514b2 go run tests/hello.go
 *
 * 2022-08-23	Rong Tao	Create this
 */
package main

import (
	"fmt"
	"bufio"
	"flag"
	"io"
	"os"
)

func lineByLine(file string) error {

	var err error

	f, err := os.Open(file)
	if err != nil {
		return err
	}

	defer f.Close()

	r := bufio.NewReader(f)
	for {
		line, err := r.ReadString('\n')
		if err == io.EOF {
			break
		} else if err != nil {
			fmt.Printf("error reading file %s", err)
			break
		}
		fmt.Print(line)
	}
	return nil
}

func main() {
	fmt.Println("Hello")
	flag.Parse()
	if len(flag.Args()) == 0 {
		fmt.Printf("usage: byLine <file1> [<file2> ...]\n")
		return
	}

	for _, file := range flag.Args() {
		err := lineByLine(file)
		if err != nil {
			fmt.Println(err)
		}
	}
}
