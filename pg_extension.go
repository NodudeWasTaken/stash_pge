package main

/*
#include <stdbool.h> // for C bool
*/
import "C"
import (
	"fmt"

	"github.com/corona10/goimagehash"
)

// https://gist.github.com/zchee/b9c99695463d8902cd33

func phashDistanceFn(phash1 int64, phash2 int64) (int64, error) {
	hash1 := goimagehash.NewImageHash(uint64(phash1), goimagehash.PHash)
	hash2 := goimagehash.NewImageHash(uint64(phash2), goimagehash.PHash)
	distance, _ := hash1.Distance(hash2)
	return int64(distance), nil
}

//export goPhashDistance
func goPhashDistance(input1 C.longlong, input2 C.longlong) C.longlong {
	arg1 := int64(input1)
	arg2 := int64(input2)

	val, _ := phashDistanceFn(arg1, arg2)

	return C.longlong(val)
}

//export goInit
func goInit() {
	fmt.Printf("stash_pge started\n")
}

func main() {}
