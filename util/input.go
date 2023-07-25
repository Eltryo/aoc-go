package util

import (
	"log"
	"os"
	"strings"
)

func GetInput() []string {
	data, error := os.ReadFile("input")
	if error != nil {
		log.Fatalln(error)
	}

	fileContent := string(data)
	lines := strings.Split(fileContent, "\n")

	return lines
}
