#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils/utils.h"

void chomp(char *str) {
  // Remove newline or carriage return char from end of string.
  int end = strlen(str) - 1;
  if (str[end] == '\n' || str[end] == '\r')
    str[end] = '\0';
}

void getInput(char *input) {
  // TODO: reject invalid input.
  printf("query: ");
  fgets(input, MAX_INPUT, stdin);
}

char *currentPointer;
char *startingPoint;

char *strtokWithBlank(char *input, char *sep) {
  char *newString;
  if (input != NULL) {
    currentPointer = input;
  };

  startingPoint = currentPointer;

  // Blank row, return empty string. This is where the method differentiates from strtok
  if (*startingPoint == *sep) {
    currentPointer++;
    return "";
  }

  for (; *currentPointer != *sep && *currentPointer != '\n' && *currentPointer != '\0'; *currentPointer++) {}
  size_t newStringSize = currentPointer - startingPoint;

  if (newStringSize == 0) {
    return NULL;
  }

  newString = malloc(newStringSize);
  stpncpy(newString, startingPoint, newStringSize);

  // advance past our delimiter so the next call starts in the correct place
  *currentPointer++;
  return  newString;
}
