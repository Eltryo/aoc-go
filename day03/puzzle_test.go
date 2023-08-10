package main

import "testing"

func TestPartOne(t *testing.T) {
	result := PartOne()
	if result != 7581 {
		t.Fatalf("PartOne() = %v, want 7581", result)
	}
}
