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
