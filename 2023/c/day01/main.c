#include <stdio.h>
#include <string.h>

#include "partOne.h"
#include "partTwo.h"

int main() {
  FILE *fptr;
  //fptr = fopen("input_1", "r");
  //fptr = fopen("example_input_1", "r");
  fptr = fopen("input_2", "r");
  //fptr = fopen("example_input_2", "r");
  if (fptr != NULL) {
    //printf("The result of part one is %d\n", partOne(fptr));
    printf("The result of part two is %d\n", partTwo(fptr));
  } else {
    printf("Not able to open the file");
  }
}
