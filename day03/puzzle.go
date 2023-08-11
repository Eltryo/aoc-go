package main

import (
	"aoc/util"
	"strings"
)

func main() {
	defer util.Timer("PartTwo")()
	println(PartTwo())
}

func PartOne() int32 {
	split := util.SplitInputByDelimiter("\n")
	var sum int32 = 0
	for _, bag := range split {
		firstCompartment := bag[:len(bag)/2]
		secondCompartment := bag[len(bag)/2:]
		for _, item := range firstCompartment {
			if strings.Contains(secondCompartment, string(item)) {
				var isAccumulated bool
				sum, isAccumulated = tryAccumulateToSum(sum, item)
				if isAccumulated {
					break
				}
			}
		}
	}

	return sum
}

func PartTwo() int32 {
	split := util.SplitInputByDelimiter("\n")
	var sum int32 = 0
	for i := 0; i < len(split); i += 3 {
		firstMate := split[i+0]
		secondMate := split[i+1]
		thirdMate := split[i+2]

		for _, item := range firstMate {
			if strings.Contains(secondMate, string(item)) {
				if strings.Contains(thirdMate, string(item)) {
					var isAccumulated bool
					sum, isAccumulated = tryAccumulateToSum(sum, item)
					if isAccumulated {
						break
					}
				}
			}
		}
	}

	return sum
}

func tryAccumulateToSum(sum int32, item int32) (int32, bool) {
	if item >= 97 && item <= 122 {
		sum += item - 96
		return sum, true
	}

	if item >= 65 && item <= 90 {
		sum += item - 38
		return sum, true
	}

	return sum, false
}
