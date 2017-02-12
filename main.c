#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query-processor.c"
#include "main.h"

#define MAX_INPUT 100

char table[MAX_RECORDS][MAX_RECORD_SIZE];
int numRows = 0;

// TODO: define struct schema based on CSV header:
// collection,content_type,document_creation_date,document_number,document_page_count,document_release_date,
// document_type,file,more1_link,more1_title,more2_link,more2_title,more3_link,more3_title,more4_link,more4_title,more5_link,more5_title,publication_date,release_decision,sequence_number,title,url


// query processor
// executor


// select * from ciadocs where title="gap"

// START: select * from ciadocs where title="____"
// THEN: select ____ from ciadocs where title="____"

// maybe later: aggregation functions - like a count iterator.
// arg takes thing it's counting, assumes it's sorted

// fn(value)

// MAIN
// calls iterators
// that read data

// Goal: sorting/hashing on disk could happen by subbing those iterators in



void loadFile(char *path) {
  printf("loading path: %s\n", path);

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

  fclose(stream);

  printf("loaded %i bytes into %i rows\n", bytesLoaded, numRows);
}

void chomp(char *str) {
  int end = strlen(str) - 1;
  if (str[end] == '\n' || str[end] == '\r')
    str[end] = '\0';
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
  SeqScanState *state = seqScanInit(table, columns);
  printf("OK...\n");

  // COUNT matching results
  // TODO: only search for `value` within field `field`
  char *result;
  int resultsCount = 0;
  for (int i = 0; i < numRows; i++) {
    result = strstr(table[i], value);
    if (result != NULL) {
      // printf("%s\n", result);
      resultsCount++;
    }
  }
  printf("%i/%i results\n", resultsCount, numRows);
}
