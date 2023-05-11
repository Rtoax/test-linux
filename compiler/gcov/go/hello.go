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
)

func main() {
	fmt.Println("Hello")
}
