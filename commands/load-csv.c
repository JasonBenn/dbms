// Analogous to postgres/src/backend/commands/copy.c, which implements the COPY command.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands/load-csv.h"
#include "main/main.h"
#include "utils/utils.h"

Record *parseRecord(char *line) {
  Record *record = (Record *) malloc(sizeof(Record));
  char *next;
  char comma = ',';

  next = strtokWithBlank(line, &comma);
  record->documentNumber = next;
  record->documentCreationDate = strtokWithBlank(NULL, &comma);
  record->documentReleaseDate = strtokWithBlank(NULL, &comma);
  record->title = strtokWithBlank(NULL, &comma);
  record->url = strtokWithBlank(NULL, &comma);

  return record;
}

void loadCsv(char *path, Table *table) {
  printf("loading path: %s\n", path);
  int numRows = 0;
  int bytesLoaded = 0;

  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  stream = fopen(path, "rb");
  if (stream == NULL)
    ; // Handle failure

  getline(&line, &len, stream);  // Read headers

  int i = 0;
  while ((read = getline(&line, &len, stream)) != -1) {
    bytesLoaded += (int) read;
    chomp(line);
    Record *record = parseRecord(line);
    (*table)[i++] = record;
    numRows++;
  }

  fclose(stream);

  printf("loaded %i bytes into %i rows\n", bytesLoaded, numRows);
}
