package main

import (
	"bufio"
	"container/list"
	"fmt"
	"log"
	"os"
	"strings"
)

func main() {
	PartOne()
}

func PartOne() {
	//file, err := os.Open("day05/input")
	file, err := os.Open("input")
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)
	stringList := list.New()
	for scanner.Scan() {
		text := scanner.Text()
		if text[0] == 32 {
			break
		}

		filteredString := FilterOutChars(text)
		stringList.PushFront(filteredString)
	}

	for e := stringList.Front(); e != nil; e = e.Next() {
		fmt.Println(e.Value)
	}
}

func FilterOutChars(s string) string {
	var sb strings.Builder
	for i, c := range s {
		if i%4 == 1 {
			sb.WriteRune(c)
		}
	}

	for sb.Len() != 9 {
		sb.WriteString(" ")
	}

	return sb.String()
}
