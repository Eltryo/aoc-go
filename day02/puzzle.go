package day02

import (
	"aoc/util"
	"errors"
	"log"
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

var resultToNumber = map[Result]int{
	Win:  6,
	Loss: 0,
	Draw: 3,
}

var letterToNumber = map[string]int{
	"X": 1,
	"Y": 2,
	"Z": 3,
	"A": 1,
	"B": 2,
	"C": 3,
}

var letterToResult = map[string]Result{
	"X": Loss,
	"Y": Draw,
	"Z": Win,
}

func PartOne() int {
	instructions := util.SplitInputByDelimiter("\n")
	sum := 0
	for _, instruction := range instructions {
		os := string(instruction[0])
		ps := string(instruction[2])
		//fmt.Printf("%v, %v \n", os, ps)

		result := compare(os, ps)
		sum += letterToNumber[ps] + resultToNumber[result]
	}

	return sum
}

func PartTwo() int {
	instructions := util.SplitInputByDelimiter("\n")
	sum := 0
	for _, instruction := range instructions {
		os := string(instruction[0])
		result := letterToResult[string(instruction[2])]
		desiredSelection, err := calculateSelectionToResult(result, os)
		if err != nil {
			log.Fatal(err)
		}

		sum += resultToNumber[result] + letterToNumber[desiredSelection]
	}

	return sum
}

func calculateSelectionToResult(result Result, os string) (string, error) {
	if result == Draw {
		return os, nil
	}

	switch os {
	case "A":
		if result == Win {
			return "Y", nil
		} else {
			return "Z", nil
		}
	case "B":
		if result == Win {
			return "Z", nil
		} else {
			return "X", nil
		}
	case "C":
		if result == Win {
			return "X", nil
		} else {
			return "Y", nil
		}
	default:
		return "", errors.New("the Selection of the opponent is not valid")
	}
}

func compare(os string, ps string) Result {
	if letterToNumber[os] == letterToNumber[ps] {
		return Draw
	}

	if os == OScissors && ps == PRock || os == ORock && ps == PPaper || os == OPaper && ps == PScissors {
		return Win
	} else {
		return Loss
	}
}
