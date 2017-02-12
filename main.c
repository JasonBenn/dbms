#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query-processor.c"
#include "main.h"
#include <stdbool.h>
#include "utils.c"

Table table;
// TODO: define struct schema based on CSV header:
// collection,content_type,document_creation_date,document_number,document_page_count,document_release_date,
// document_type,file,more1_link,more1_title,more2_link,more2_title,more3_link,more3_title,more4_link,more4_title,more5_link,more5_title,publication_date,release_decision,sequence_number,title,url

void loadFile(char *path) {
  printf("loading path: %s\n", path);

  int numRows = 0;
  FILE *stream = fopen(path, "rb");
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int bytesLoaded = 0;
  int i = 0;
  while ((read = getline(&line, &len, stream)) != -1) {
    bytesLoaded += (int) read;
    // TODO: rows should be instances of struct instead of string
    strncpy(table[i++], line, MAX_RECORD_SIZE);
    numRows++;
  }

  strncpy(table[i], TABLE_TERMINATOR, MAX_RECORD_SIZE);
  fclose(stream);

  printf("loaded %i bytes into %i rows\n", bytesLoaded, numRows);
}

void getInput(char *input) {
  printf("query: ");
  fgets(input, MAX_INPUT, stdin);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  // TODO: accept any number of files
  loadFile(argv[1]);

  // // Invert comments of this paragraph for user input.
  // char input[MAX_INPUT];
  // getInput(input);
  char input[MAX_INPUT] = "title:HAINAN";

  // PARSE query of form field:value
  // TODO: handle bad input
  char *field = strtok(input, ":");
  char *value = strtok(NULL, ":");
  chomp(value);

  // QUERY PROCESSOR
  char *columns[] = { "title" };
  SeqScanState *state = seqScanInit(&table, columns);
  printf("OK...\n");

  printf("tt %s\n", TABLE_TERMINATOR);
  printf("cmp: %i\n", strcmp(*seqScanNext(state), TABLE_TERMINATOR));
  // A couple problems here. One, the csv is UTF-8, so strcmp is returning garbage.
  // But that should actually be all right... I'm just waiting for TABLE_TERMINATOR.
  // I do wish that there was a cleaner way to return an EOF value. Everything
  // returned from that func has to be the same value, though :/
  printf("cmp: %i\n", strcmp(*seqScanNext(state), TABLE_TERMINATOR));

  // Another problem: segfault after the third seqScanNext(state). In lldb:
  //  error: Execution was interrupted, reason: EXC_BAD_ACCESS (code=1, address=0x10b71c670).
  //      The process has been returned to the state before expression evaluation.

//  printf("cmp: %i\n", strcmp(*seqScanNext(state), TABLE_TERMINATOR));
//  while (strcmp(*seqScanNext(state), TABLE_TERMINATOR) != 0)
//      printf("state %i", state->currentId);
//
//  printf("numRecords: %i\n", state->currentId);

}
