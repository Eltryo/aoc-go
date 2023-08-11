package main

import (
	"aoc/util"
	"log"
	"strconv"
	"strings"
)

func main() {
	defer util.Timer("PartTwo")()
	println(PartTwo())
}

func PartOne() int {
	pairs := util.SplitInputByDelimiter("\n")
	var sum = 0
	for _, pair := range pairs {
		assignments := strings.Split(pair, ",")
		firstAssignment := assignments[0]
		secondAssignment := assignments[1]

		fMin, fMax := getMinMaxAssignment(firstAssignment)
		sMin, sMax := getMinMaxAssignment(secondAssignment)
		if fMin <= sMin && fMax >= sMax || sMin <= fMin && sMax >= fMax {
			sum++
		}
	}

	return sum
}

func PartTwo() int {
	pairs := util.SplitInputByDelimiter("\n")
	var sum = 0
	for _, pair := range pairs {
		assignments := strings.Split(pair, ",")
		firstAssignment := assignments[0]
		secondAssignment := assignments[1]

		fMin, fMax := getMinMaxAssignment(firstAssignment)
		sMin, sMax := getMinMaxAssignment(secondAssignment)

		if isBetweenAssignment(fMin, sMin, sMax) || isBetweenAssignment(fMax, sMin, sMax) || isBetweenAssignment(sMin, fMin, fMax) || isBetweenAssignment(sMax, fMin, fMax) {
			sum++
		}
	}

	return sum
}

func isBetweenAssignment(boundary int, min int, max int) bool {
	if boundary >= min && boundary <= max {
		return true
	}

	return false
}

func getMinMaxAssignment(assignment string) (int, int) {
	minMax := strings.Split(assignment, "-")
	min, err1 := strconv.Atoi(minMax[0])
	if err1 != nil {
		log.Fatal(err1)
	}

	max, err2 := strconv.Atoi(minMax[1])
	if err2 != nil {
		log.Fatal(err2)
	}

	return min, max
}
