package main

import (
	"aoc/util"
	"strings"
)

func main() {
	PartOne()
}

func PartOne() int32 {
	split := util.SplitInputByDelimiter("\n")
	var sum int32 = 0
	for _, bag := range split {
		firstCompartment := bag[:len(bag)/2]
		secondCompartment := bag[len(bag)/2:]
		for _, item := range firstCompartment {
			//println(item)
			if strings.Contains(secondCompartment, string(item)) {
				if item >= 97 && item <= 122 {
					sum += item - 96
				}

				if item >= 65 && item <= 90 {
					sum += item - 38
				}
			}
		}
	}

	return sum
}

//func PartTwo() int {}

//func calcValueOfItem()