package day01

import (
	"aoc/util"
	"log"
	"strconv"
)

func PartOne() int {
	bag := util.GetInput()
	max := 0
	sum := 0
	for _, food := range bag {
		if food == "" {
			if sum > max {
				max = sum
			}
			sum = 0
			continue
		}

		calories, err := strconv.Atoi(food)
		if err != nil {
			log.Fatal(err)
		}

		sum += calories
	}

	return max
}
