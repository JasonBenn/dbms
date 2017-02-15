#include "main.h"


struct {
  Table *table;
  int position;
  int numColumns;
} typedef SeqScanState;

SeqScanState *seqScanInit(Table *table, int numColumns);
Record *seqScanNext(SeqScanState *state);
void seqScanClose(SeqScanState *state);
