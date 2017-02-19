// Analogous to postgres/src/backend/commands/copy.c, which implements the COPY command.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands/load-csv.h"
#include "main/main.h"
#include "utils/utils.h"

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

  read = getline(&line, &len, stream);

  int i = 0;
  while ((read = getline(&line, &len, stream)) != -1) {
    bytesLoaded += (int) read;
    chomp(line);
    strncpy((*table)[i], line, MAX_RECORD_SIZE);
    i++;
    numRows++;
  }

  fclose(stream);

  printf("loaded %i bytes into %i rows\n", bytesLoaded, numRows);
}
