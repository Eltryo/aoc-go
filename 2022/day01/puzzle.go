package main

import (
	"aoc/util"
	"log"
	"sort"
	"strconv"
	"strings"
)

func PartOne() int {
	bag := util.SplitInputByDelimiter("\n")
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

func PartTwo() int {
	bag := util.SplitInputByDelimiter("\n\n")
	caloriesOfElves := util.Map(bag, convertContentToSum)
	sort.Slice(caloriesOfElves, func(i, j int) bool {
		return caloriesOfElves[i] > caloriesOfElves[j]
	})

	var result int
	for i := 0; i < 3; i++ {
		result += caloriesOfElves[i]
	}

	return result
}

func convertContentToSum(s string) int {
	foods := strings.Split(s, "\n")
	sum := 0
	for _, food := range foods {
		val, err := strconv.Atoi(food)
		if err != nil {
			log.Fatal(err)
		}

		sum += val
	}

	return sum
}
