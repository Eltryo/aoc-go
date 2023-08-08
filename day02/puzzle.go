package main

import (
	"aoc/util"
)

type Result int

const (
	ORock     = "A"
	OPaper    = "B"
	OScissors = "C"
	PRock     = "X"
	PPaper    = "Y"
	PScissors = "Z"
)

const (
	Win Result = iota
	Loss
	Draw
)

var mResult = map[Result]int{
	Win:  6,
	Loss: 0,
	Draw: 3,
}

var mSelection = map[string]int{
	"X": 1,
	"Y": 2,
	"Z": 3,
	"A": 1,
	"B": 2,
	"C": 3,
}

func PartOne() int {
	instructions := util.SplitInputByDelimiter("\n")
	sum := 0
	for _, instruction := range instructions {
		os := string(instruction[0])
		ps := string(instruction[2])
		//fmt.Printf("%v, %v \n", os, ps)

		result := compare(os, ps)
		sum += mSelection[ps] + mResult[result]
	}

	return sum
}

func compare(os string, ps string) Result {
	if mSelection[os] == mSelection[ps] {
		return Draw
	}

	if os == OScissors && ps == PRock || os == ORock && ps == PPaper || os == OPaper && ps == PScissors {
		return Win
	} else {
		return Loss
	}
}
