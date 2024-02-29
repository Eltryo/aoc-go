#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

#define LINE_SIZE 1024

typedef struct {
    char *key;
    int value;
} STRING_TO_INT;

STRING_TO_INT SpelledToInt[9] = {
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
};

char *substring(char *str, int start, int end) {
    int substringLen = end - start;
    char *substr = calloc(substringLen + 1, 1);

    strncpy(substr, str + start, substringLen);

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

char *reverseString(char *str) {
    char *revStr = calloc(strlen(str) + 1, 1);
    for (int i = 0; i < strlen(str); i++) {
        revStr[i] = str[strlen(str) - i - 1];
    }

    return revStr;
}

bool spelledNumOffset(char *line, regmatch_t *pmatch, char *pattern) {
    regex_t regex;

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        regfree(&regex);
        exit(EXIT_FAILURE);
    }

    int regexecResult = regexec(&regex, line, 1, pmatch, 0);
    if (regexecResult == REG_NOMATCH) {
        printf("No match found\n");
        regfree(&regex);
        return false;
    } else if (regexecResult != 0) {
        char errBuff[100];
        size_t errBuffSize = sizeof(errBuff);

        regerror(regexecResult, &regex, errBuff, errBuffSize);

        regfree(&regex);
        exit(EXIT_FAILURE);
    }

    regfree(&regex);
    return true;
}

int numOffset(char *line) {
    if(strlen(line) == 0) return -1;
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] >= 48 && line[i] <= 57) {
            return i;
        }
    }

    return -1;
}

bool chomp(char *str) {
    if (strlen(str) == 0)
        return false;

    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
        return true;
    } else {
        return false;
    }
}

int partTwo(FILE *fptr) {
    char line[LINE_SIZE];
    int result = 0;
    regmatch_t pmatch[1];
    char *pattern = "(one|two|three|four|five|six|seven|eight|nine)";
    char *reversePattern = "(eno|owt|eerht|ruof|evif|xis|neves|thgie|enin)";

    while (fgets(line, LINE_SIZE, fptr)) {
        chomp(line);
        char *revLine = reverseString(line);

        int firstNumOffset = numOffset(line);
        int revLineNumOffset = numOffset(revLine);
        int lastNumOffset =
            revLineNumOffset == -1 ? -1 : strlen(line) - revLineNumOffset - 1;

        int lastSpelledValue = -1;
        int lastSpelledOffset = -1;
        int firstSpelledValue = -1;
        int firstSpelledOffset = -1;
        bool isMatch = spelledNumOffset(line, pmatch, pattern);
        if (isMatch) {
            char *firstWord = substring(line, pmatch[0].rm_so, pmatch[0].rm_eo);
            firstSpelledValue = spelledToInt(firstWord);
            firstSpelledOffset = pmatch[0].rm_so;

            spelledNumOffset(revLine, pmatch, reversePattern);
            char *lastRevWord = substring(revLine, pmatch[0].rm_so, pmatch[0].rm_eo);
            char *lastWord = reverseString(lastRevWord);
            lastSpelledValue = spelledToInt(lastWord);
            lastSpelledOffset = strlen(line) - pmatch[0].rm_eo;

            free(firstWord);
            free(lastWord);
            free(lastRevWord);
        }

        int tens =
            firstNumOffset == -1 ? firstSpelledOffset == -1 ? 0 : firstSpelledValue
            : firstSpelledOffset == -1            ? line[firstNumOffset] - '0'
            : firstNumOffset < firstSpelledOffset ? line[firstNumOffset] - '0'
            : firstSpelledValue;

        int ones = lastNumOffset == -1
            ? lastSpelledOffset == -1 ? 0 : lastSpelledValue
            : lastSpelledOffset == -1           ? line[lastNumOffset] - '0'
            : lastNumOffset > lastSpelledOffset ? line[lastNumOffset] - '0'
            : lastSpelledValue;

        result += tens * 10 + ones;

        free(revLine);
    }

    return result;
}
