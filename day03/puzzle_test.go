package main

import "testing"

func TestPartOne(t *testing.T) {
	result := PartOne()
	if result != 7581 {
		t.Fatalf("PartOne() = %v, want 7581", result)
	}
}

func TestPartTwo(t *testing.T) {
	result := PartTwo()
	if result != 0 {
		t.Fatalf("PartTwo() = %v, want 0", result)
	}
}
