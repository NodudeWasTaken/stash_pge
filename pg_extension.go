package main

import "C"
import (
	"fmt"
	"path/filepath"
	"regexp"

	"github.com/corona10/goimagehash"
	lru "github.com/hashicorp/golang-lru/v2"
)

// https://gist.github.com/zchee/b9c99695463d8902cd33

const regexCacheSize = 10

var regexCache *lru.Cache[string, *regexp.Regexp]

//export goBasename
func goBasename(input *C.char) *C.char {
	arg1 := C.GoString(input)

	base := filepath.Base(arg1)

	return C.CString(base)
}

//export goRegexpMatch
func goRegexpMatch(cpattern *C.char, cinput *C.char) bool {
	input := C.GoString(cinput)
	pattern := C.GoString(cpattern)

	compiled, ok := regexCache.Get(pattern)
	if !ok {
		var err error
		compiled, err = regexp.Compile(pattern)
		if err != nil {
			fmt.Printf("RegexpMatch error: %v", err)
			return false
		}
		regexCache.Add(pattern, compiled)
	}

	return compiled.MatchString(input)
}

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

func main() {
	regexCache, _ = lru.New[string, *regexp.Regexp](regexCacheSize)
}
