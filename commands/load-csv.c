// Analogous to postgres/src/backend/commands/copy.c, which implements the COPY command.
#include <stdio.h>
#include <string.h>
#include "commands/load-csv.h"
#include "main/main.h"

void loadCsv(char *path, Table *table) {
  printf("loading path: %s\n", path);

  int numRows = 0;
  FILE *stream = fopen(path, "rb");
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int bytesLoaded = 0;
  int i = 0;
  while ((read = getline(&line, &len, stream)) != -1) {
    printf("read %lu line %s\n", read, line);
    bytesLoaded += (int) read;
    // TODO: this "table" is an array of strings. It should be an array of Records.
    printf("index %i\n\n", sizeof(Record) * i);
    strncpy(*table[(sizeof(Record) * i)], line, MAX_RECORD_SIZE);
    strncpy(*table[i], line, MAX_RECORD_SIZE);
    i++;
    numRows++;
  }

  fclose(stream);

  printf("loaded %i bytes into %i rows\n", bytesLoaded, numRows);
}
