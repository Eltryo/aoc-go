#include <stdio.h>
#include <string.h>

#define LINE_SIZE 1024

int partOne(FILE *fptr) {
  int result = 0;
  char line[LINE_SIZE];

  // read the next line into a buffer
  while (fgets(line, LINE_SIZE, fptr)) {
    // search first int
    for (int i = 0; i < strlen(line) - 1; i++) {
      if (line[i] >= 48 && line[i] <= 57) {
        int firstNum = line[i] - '0';
        result += firstNum * 10;
        break;
      }
    }

    // search last int
    for (int i = strlen(line) - 2; i >= 0; i--) {
      printf("%c : %d\n", line[i], i);
      if (line[i] >= 48 && line[i] <= 57) {
        int secondNum = line[i] - '0';
        result += secondNum;
        break;
      }
    }
  }

  return result;
}
