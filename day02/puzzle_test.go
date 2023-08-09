package day02

import "testing"

func TestPartOne(t *testing.T) {
	result := PartOne()
	if result != 14069 {
		t.Fatalf(`PartOne() = %v, want 14069`, result)
	}
}

func TestPartTwo(t *testing.T) {
	result := PartTwo()
	if result != 12411 {
		t.Fatalf(`PartTwo() = %v, want 12411`, result)
	}
}
