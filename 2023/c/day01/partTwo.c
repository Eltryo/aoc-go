#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 1024

typedef struct {
  int first;
  int last;
} FL_NUM_OFFSET;

typedef struct {
  int first;
  int last;
} FL_SPELLED_OFFSET;

FL_SPELLED_OFFSET *flSpelledOffset(char *line) {
  regex_t regex;
  regmatch_t *pmatch;
  char *pattern = "one|two|three|four|five|six|seven|eigtht|nine";
  FL_SPELLED_OFFSET *offsets = malloc(2 * sizeof(int));
  offsets->first = -1;
  offsets->last = -1;

  if (regcomp(&regex, pattern, 0))
    exit(EXIT_FAILURE);
  printf("regex compiled\n");

  if(regexec(&regex, line, 1, pmatch, 0) == REG_NOMATCH)
    return NULL;
  printf("first match found\n");

  offsets->first = pmatch[0].rm_so;

  size_t inputLen = strlen(line);
  size_t offset = pmatch[0].rm_eo;
  while(offset < inputLen && regexec(&regex, line + offset, 1, pmatch, 0) == 0){
    printf("offset is: %lu\n", offset);
    offset += pmatch[0].rm_eo;
  }

  size_t lenOfLastMatch = pmatch[0].rm_eo - pmatch[0].rm_so;
  offsets->last = offset - lenOfLastMatch;

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

  while (fgets(line, LINE_SIZE, fptr)) {
    FL_NUM_OFFSET *numOffsets = flNumOffset(line);
    if (numOffsets != NULL) printf("Number offsets: %d, %d\n", numOffsets->first, numOffsets->last);
    free(numOffsets);

    FL_SPELLED_OFFSET * spelledOffsets = flSpelledOffset(line);
    if(spelledOffsets != NULL) printf("Spelled offsets %d, %d\n", spelledOffsets->first, spelledOffsets->last);
    free(spelledOffsets);
  }

  return 0;
}
