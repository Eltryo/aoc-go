#include <stdio.h>
#include <string.h>

#define LINE_SIZE 1024

int partOne(FILE *fptr) {
  int result = 0;
  char line[LINE_SIZE];

  while (fgets(line, LINE_SIZE, fptr)) {
    for (int i = 0; i < strlen(line) - 1; i++) {
      if (line[i] >= 48 && line[i] <= 57) {
        int firstNum = line[i] - '0';
        result += firstNum * 10;
        break;
      }
    }

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
