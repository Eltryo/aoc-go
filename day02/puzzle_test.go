package main

import "testing"

func TestPartOne(t *testing.T) {
	result := PartOne()
	if result != 14069 {
		t.Fatalf(`PartOne() = %v, want 14069`, result)
	}
}
