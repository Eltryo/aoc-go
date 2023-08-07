package util

import (
	"log"
	"os"
	"strings"
)

func SplitInputByDelimiter(delimiter string) []string {
	data, error := os.ReadFile("input")
	if error != nil {
		log.Fatalln(error)
	}

	fileContent := strings.TrimSpace(string(data))
	lines := strings.Split(fileContent, delimiter)

	return lines
}

func Map[T, U any](ts []T, f func(T) U) []U {
	us := make([]U, len(ts))
	for i := range us {
		us[i] = f(ts[i])
	}

	return us
}
