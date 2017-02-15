#include <stdio.h>
#include <stdlib.h>
#include "main.h"


struct {
  Table *table;
  int currentId; // Should be location of memory buffer.
  int numColumns;
  char *columns[];
} typedef SeqScanState;

SeqScanState *seqScanInit(Table *table, char *columns[], int numColumns) {
  SeqScanState *state = (SeqScanState *) malloc(sizeof(SeqScanState));
  state->table = table;
  state->currentId = 0;
  state->numColumns = 10; // TODO: populate with data from a header in our binary file format?
  *(state->columns) = *columns;
  return state;
}

Record *seqScanNext(SeqScanState *state) {
//  printf("%i\n", state->currentId);
  //  printf("%s\n", *state->table[state->currentId]);
  Record *record = &(state->table[sizeof(Record) * state->currentId]);
  if (strcmp(*record, TABLE_TERMINATOR) == 0) {
    return &TABLE_TERMINATOR;
  } else {
    state->currentId++;
    return record;
  }
  return &TABLE_TERMINATOR;
}

void seqScanClose(SeqScanState *state) {
  free(state);
  return;
}
