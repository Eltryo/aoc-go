package main

import "testing"

func TestPartOne(t *testing.T) {
	maxCalories := PartOne()
	if maxCalories != 69281 {
		t.Fatalf(`PartOne() = %v, want 69281`, maxCalories)
	}
}

func TestPartTwo(t *testing.T) {
	sumOfTopThree := PartTwo()
	if sumOfTopThree != 201524 {
		t.Fatalf(`PartTwo() = %v, want 201524`, sumOfTopThree)
	}
}
