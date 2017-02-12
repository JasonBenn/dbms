#include <stdio.h>
#include <stdlib.h>
#include "main.h"

struct {
  Table *table;
  char *columns[];
} typedef SeqScanState;

struct {
  int id;
  int salary;
  char *name;
} typedef Record;

SeqScanState *seqScanInit(Table *table, char *columns[]) {
  SeqScanState *i = (SeqScanState *) malloc(sizeof(SeqScanState));
  i->table = table;
  *(i->columns) = *columns;
  return i;
}

Record seqScanNext(SeqScanState *state) {
  Record record = {};
  return record;
}

void seqScanClose(SeqScanState *state) {
  free(state);
  return;
}
