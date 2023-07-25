package day01

import "testing"

func TestPartOne(t *testing.T) {
	maxCalories := PartOne()
	if maxCalories != 69281 {
		t.Fatalf(`PartOne() = %v, want 69281`, maxCalories)
	}
}
