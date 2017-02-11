#include <stdio.h>
#include <stdlib.h>
#include "dbms.h"

#define MAX_RECORD_SIZE 1500

struct {
  char *Table;
  char *columns[];
} typedef SeqScanState;

struct {
  int id;
  int salary;
  char *name;
} typedef Record;

SeqScanState *seqScanInit(char Table, char *columns[]) {
  SeqScanState *i = (SeqScanState *) malloc(sizeof(SeqScanState));
  // How do I store a pointer to this table?
  i->table = table;
  *(i->columns) = *columns; // Sets first pointer of i->columns to first pointer of columns.
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

// int main(void) {
//   char *columns[] = { "title" };
//   SeqScanState *state = seqScanInit("ciadocs", columns);
//   printf("OK...\n");
// }
