#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

#define LINE_SIZE 1024

typedef struct {
  int first;
  int last;
} FL_NUM_OFFSET;

typedef struct {
  int first;
  int last;
  int firstVal;
  int lastVal;
} FL_SPELLED_OFFSET;

typedef struct {
  char *key;
  int value;
} STRING_TO_INT;

STRING_TO_INT SpelledToInt[9] = {
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
};

// h a l l o h i
// 0 1 2 3 4 5 6
//   *     *
char *substring(char *str, int start, int end) {
  int substringLen = end - start;
  char *substr = calloc(substringLen + 1, 1);

  strncpy(substr, str + start, substringLen);

  printf("substring is: %s\n", substr);

  return substr;
}

int spelledToInt(char *spelledNum) {
  size_t size = sizeof(SpelledToInt) / sizeof(STRING_TO_INT);
  for (int i = 0; i < size; i++) {
    STRING_TO_INT spelledToIntEl = SpelledToInt[i];
    if (strcmp(spelledToIntEl.key, spelledNum) == 0) {
      return spelledToIntEl.value;
    }
  }

  return -1;
}

FL_SPELLED_OFFSET *flSpelledOffset(char *line) {
  regex_t regex;
  regmatch_t pmatch[1];
  char *pattern = "(one|two|three|four|five|six|seven|eight|nine)";
  FL_SPELLED_OFFSET *offsets = malloc(4 * sizeof(int));
  offsets->first = -1;
  offsets->last = -1;
  offsets->firstVal = -1;
  offsets->lastVal = -1;

  if (regcomp(&regex, pattern, REG_EXTENDED)) {
    regfree(&regex);
    exit(EXIT_FAILURE);
  }
  printf("regex compiled\n");

  printf("The input line is: %s", line);
  int regexecResult = regexec(&regex, line, 1, pmatch, 0);
  if (regexecResult == REG_NOMATCH) {
    printf("No match found\n");
    regfree(&regex);
    return offsets;
  } else if (regexecResult != 0) {
    char errBuff[100];
    size_t errBuffSize = sizeof(errBuff);

    regerror(regexecResult, &regex, errBuff, errBuffSize);
    fprintf(stderr, "Error executing regular expression: %s\n", errBuff);

    regfree(&regex);
    exit(EXIT_FAILURE);
  }
  printf("first match found\n");

  offsets->first = pmatch[0].rm_so;
  char *firstWord = substring(line, pmatch[0].rm_so, pmatch[0].rm_eo);
  int firstValue = spelledToInt(firstWord);
  free(firstWord);
  if (firstValue == -1) {
    fprintf(stderr,
            "Error when mapping from spelled number to integer value: \n");
    exit(EXIT_FAILURE);
  }

  offsets->firstVal = firstValue;

  size_t inputLen = strlen(line);
  size_t offset = pmatch[0].rm_eo;
  while (offset < inputLen &&
         regexec(&regex, line + offset, 1, pmatch, 0) == 0) {
    offset += pmatch[0].rm_eo;
  }

  size_t lenOfLastMatch = pmatch[0].rm_eo - pmatch[0].rm_so;
  offsets->last = offset - lenOfLastMatch;

  char *lastWord = substring(line, offset - lenOfLastMatch, offset);
  int lastValue = spelledToInt(lastWord);
  free(lastWord);
  if (lastValue == -1) {
    fprintf(stderr,
            "Error when mapping from spelled number to integer value: \n");
    exit(EXIT_FAILURE);
  }

  offsets->lastVal = lastValue;

  regfree(&regex);
  return offsets;
}

FL_NUM_OFFSET *flNumOffset(char *line) {
  FL_NUM_OFFSET *offsets = malloc(2 * sizeof(int));
  offsets->first = -1;
  offsets->last = -1;

  for (int i = 0; i < strlen(line) - 1; i++) {
    if (line[i] >= 48 && line[i] <= 57) {
      offsets->first = i;
      break;
    }
  }

  for (int i = strlen(line) - 2; i >= 0; i--) {
    if (line[i] >= 48 && line[i] <= 57) {
      offsets->last = i;
      break;
    }
  }

  return offsets;
}

int partTwo(FILE *fptr) {
  char line[LINE_SIZE];
  int result = 0;

  while (fgets(line, LINE_SIZE, fptr)) {
    FL_NUM_OFFSET *numOffsets = flNumOffset(line);
    FL_SPELLED_OFFSET *spelledOffsets = flSpelledOffset(line);
    if (numOffsets == NULL || spelledOffsets == NULL) {
      fprintf(stderr, "Offsets are NULL");
      exit(EXIT_FAILURE);
    }

    int firstNumOffset = numOffsets->first;
    int lastNumOffset = numOffsets->last;
    int firstSpelledOffset = spelledOffsets->first;
    int lastSpelledOffset = spelledOffsets->last;
    int firstSpelledValue = spelledOffsets->firstVal;
    int lastSpelledValue = spelledOffsets->lastVal;

    free(numOffsets);
    free(spelledOffsets);

    int tens = firstNumOffset == -1       ? firstSpelledValue
               : firstSpelledOffset == -1 ? line[firstNumOffset] - '0'
               : firstNumOffset < firstSpelledOffset
                   ? line[firstNumOffset] - '0'
                   : firstSpelledValue;
    int ones = lastNumOffset == -1                 ? lastSpelledValue
               : lastSpelledOffset == -1           ? line[lastNumOffset] - '0'
               : lastNumOffset > lastSpelledOffset ? line[lastNumOffset] - '0'
                                                   : lastSpelledValue;

    printf("tens: %d\n", tens);
    printf("ones: %d\n", ones);

    result += tens * 10 + ones;
  }

  return result;
}
