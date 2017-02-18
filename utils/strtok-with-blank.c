#include <stdlib.h>
#include <string.h>
#include "utils/strtok-with-blank.h"

char *current_pointer;
char *starting_point;
char *strtok_with_blank(char *input, char *sep) {
  char *new_string;
  if (input != NULL) { current_pointer = input; };

  starting_point = current_pointer;

  //Blank row, return empty string. This is where the method differentiates from strtok
  if (*starting_point == *sep) {
    current_pointer++;
    return "" ;
  }
  for (;*current_pointer != *sep && *current_pointer != '\n' && *current_pointer != '\0';*current_pointer++){}
  size_t new_string_size = current_pointer - starting_point;
  if (new_string_size == 0){
    return NULL;
  }
  new_string = malloc(new_string_size);
  stpncpy(new_string, starting_point, new_string_size);

  //advance past our delimeter so the next call starts in the correct place
  *current_pointer++;
  return  new_string;
}
