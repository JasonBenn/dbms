#include <stdlib.h>
#include <stdio.h>

// TERMINOLOGY:
// record = an entire row
// tuple = the selected fields of a record
// tupleFromRecord = takes record and selected fields, returns tuple

struct {
  char *table;
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

int main(void) {
  // SELECT post.title
  // FROM posts JOIN votes
  // ON post.id = vote.postId
  // // WHERE votes.count > 50

  JoinTableArgs inner;
  inner.table = "posts";
  inner.hashFields = (char *[]) {"id"};
  inner.tupleFields = (char *[]) {"title"};

  JoinTableArgs outer;
  outer.table = "votes";
  outer.hashFields = (char *[]) {"postId"};
  outer.tupleFields = (char *[]) {""};

  hashJoinInit(&inner, &outer);
  // WHILE (tuple = hashJoinNext) != NULL
    // PRINT tuple
  printf("ok\n");
}
