#include <stdio.h>
#include <stdlib.h>
#include "main.h"

// TODO: move to main.h, inside #ifndef block.
extern Record TABLE_TERMINATOR;
Record TABLE_TERMINATOR = "END OF TABLE";

// Operator: SeqScan
struct {
  Table *table;
  int currentId; // Should be location of memory buffer.
  char *columns[];
} typedef SeqScanState;

SeqScanState *seqScanInit(Table *table, char *columns[]) {
  SeqScanState *state = (SeqScanState *) malloc(sizeof(SeqScanState));
  state->table = table;
  state->currentId = 0;
  *(state->columns) = *columns;
  return state;
}

Record *seqScanNext(SeqScanState *state) {
//  printf("%i\n", state->currentId);
  //  printf("%s\n", *state->table[state->currentId]);
  Record *record = state->table[state->currentId];
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


// It's not possible in C to define a generic Operator type, right...?
//struct Operator { ... };
// Then I'd be able to i.e., reuse close for a bunch of different operators.
//extern Operator SeqScan = { &seqScanInit, &seqScanNext, &close };

// Add some joins