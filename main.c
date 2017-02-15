#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "utils/utils.c"
// TODO: loading from CSV every run -> loading from file in our binary format
#include "commands/copy-from-csv.h"


Table table;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  // TODO: accept any number of files
  loadCsv(argv[1], &table);

  // Example valid input: "title:HAINAN";
  char input[MAX_INPUT];
  getInput(input);

  // PARSE query of form field:value
  // TODO: handle bad input
  char *field = strtok(input, ":");
  char *value = strtok(NULL, ":");
  chomp(value);

  // QUERY PROCESSOR
  // TODO
}
