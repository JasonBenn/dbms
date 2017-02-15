#include <stdio.h>
#include <string.h>
#include "main.h"
#include "utils/utils.h"
// TODO: loading from CSV every run -> loading from file in our binary format
#include "commands/load-csv.h"


Table table;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Need at least one argument.\n");
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

  // TODO: query processor
}
