package main

import "testing"

func TestPartOne(t *testing.T) {
	result := PartOne()
	if result != 0 {
		t.Fatalf("PartOne() = %v, want 532", result)
	}
}

func TestPartTwo(t *testing.T) {
	result := PartTwo()
	if result != 0 {
		t.Fatalf("PartTwo() = %v, want 854", result)
	}
}
