#include <stdio.h>
#include <stdlib.h>
#include "main.h"


SeqScanState *seqScanInit(Table *table, int numColumns) {
  SeqScanState *state = (SeqScanState *) malloc(sizeof(SeqScanState));
  state->table = table;
  state->position = 0;
  state->numColumns = 10; // TODO: populate with data from a header in our binary file format...?
  return state;
}

Record *seqScanNext(SeqScanState *state) {
  // ?? Record *record = &(state->table[sizeof(Record) * state->position]);
  Record *record;
  if (state->position == state->numColumns) {
    return NULL;
  } else {
    state->position++;
    return record;
  }
}

void seqScanClose(SeqScanState *state) {
  free(state);
  return;
}
