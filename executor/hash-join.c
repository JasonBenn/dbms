#include <stdlib.h>
#include <stdio.h>
#include "main.h"

struct {
  Table *table;
  char **hashFields;
  char **tupleFields;
} typedef JoinTableArgs;

struct {
  JoinTableArgs *inner;
  JoinTableArgs *outer;
} typedef HashJoinState;

HashJoinState *hashJoinInit(JoinTableArgs *inner, JoinTableArgs *outer) {
  // ALLOC state
  HashJoinState *state = (HashJoinState *) malloc(sizeof(HashJoinState));
  state->inner = inner;
  state->outer = outer;

  // ALLOC hashTable

  // FOR record in seqScan(inner).next:
    // hash = hashRecord(record)
    // hashTable[hash] = tupleFromRecord(record, innerFields)
  return state;
}

void hashJoinNext(void) {
  // FOR record in seqScan(outer).next:
    // hash = hashRecord(record)
    // innerTuple = hashTable[hash]
    // if innerTuple?
      // return join(record, innerTuple)
}

void hashJoinClose(void) {
  // FREE hashTable
}
