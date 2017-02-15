#include <stdlib.h>
#include <stdio.h>
#include "main.h"

// This file is currently it's own little world.
// Reconciling with the rest of the project will require settling on single Table & Record typedefs.

// TERMINOLOGY:
// record = an entire row
// projection = the selected fields of a record
// project = takes record and selected fields, returns projection

// STUB DATA
// 25: innermost array.
#define NUM_FIELDS 3
#define NUM_RECORDS 5
typedef char *Table[NUM_RECORDS][NUM_FIELDS];
typedef char *Record[NUM_FIELDS];
typedef char **Projection; // Any number of fields, any length of field.

#define HASHTABLE_BUCKETS 255

Table posts = {
  {"1", "How do I C"},
  {"2", "Why does clang hate me"}
};
int postsLength = 2;

Table authors = {
  {"1", "1", "Bert"},
  {"2", "1", "Ernie"},
  {"3", "2", "Elmo"},
  {"4", "3", "The Animal"}
};
int authorsLength = 4;

struct {
  Table *table;
  int hashFields[NUM_FIELDS];
  int numHashFields;
  int tupleFields[NUM_FIELDS];
  int numTupleFields;
} typedef JoinTableArgs;

struct {
  JoinTableArgs *inner;
  JoinTableArgs *outer;
  char **hashTable;
} typedef HashJoinState;

// void printTable(Table *table) {
//   printf("")
// }

int hashRecord(Record *fieldsToHash) {
  return 1;
}

Projection *project(Record *record, int *tupleFields, int numTupleFields) {
  Projection *projection;
  printf("tupleFields[0]: %i\n", tupleFields[1]);
  for (int i = 0; i < numTupleFields; i++) {
    printf("tupleFields[%i]: %i", i, tupleFields[i]);
    // printf("%i maps to %s", tupleFields[i], (*record)[tupleFields[i]]);
    // (*projection)[i] = (*record)[tupleFields[i]];
  }
  printf("\n");
  return projection;
}

void printRecord(Record *record) {
  for (int i = 0; i < NUM_FIELDS; i++) {
    printf("%s ", (*record)[i]);
  }
  printf("\n");
}

HashJoinState *hashJoinInit(JoinTableArgs *inner, JoinTableArgs *outer) {
  // ALLOC state
  HashJoinState *state = (HashJoinState *) malloc(sizeof(HashJoinState));
  state->inner = inner;
  state->outer = outer;

  // ALLOC hashTable. Will be array of pointers, or null.
  state->hashTable = malloc(sizeof(char *) * HASHTABLE_BUCKETS);
  // NULL out the table.

  for (int i = 0; i < 4; i++) {
    Record *record = (Record *) ((*outer->table)[i]);
    printRecord(record);
    Projection *hashValues = project(record, outer->hashFields, outer->numHashFields);
    printf("hash: %i\n\n", hashRecord(record));
  }

  // FOR record in filterSeqScan(inner).next:
  // for (int i = 0; i < postsLength; i++) {
  //   Record *record = (*(inner->table))[i];
  //   char **fieldsToHash = project(record, inner->hashFields);
  //   hash = hashRecord(fieldsToHash);
  //   hashTable[hash] = project(record, inner->tupleFields);
  // }

    // hash = hashRecord(record)
    // hashTable[hash] = project(record, innerFields)
  return state;
}

// Add some joins
// Simple hash function:
  // XOR all bytes together gives 256 buckets.
  // To make it smaller, mod by a power of 2.
  // For more buckets, XOR adjacent buckets

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

int main(void) {
  // SELECT post.title, author.name
  // FROM posts JOIN author
  // ON post.id = author.postId

  JoinTableArgs inner;
  inner.table = &posts;
  // schema: id, title
  inner.hashFields[0] = 0; // id
  inner.numHashFields = 1;
  inner.tupleFields[0] = 1; // title
  inner.numTupleFields = 1;

  JoinTableArgs outer;
  outer.table = &authors;
  // schema: id, postId, name
  outer.hashFields[0] = 1; // postId
  outer.numHashFields = 1;
  outer.tupleFields[0] = 2; // name
  outer.numTupleFields = 1;

  hashJoinInit(&inner, &outer);
  // WHILE (projection = hashJoinNext) != NULL
    // PRINT projection
  printf("ok\n");
}
