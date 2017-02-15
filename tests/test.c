#include <stdio.h>
#include <stdbool.h>
#include "tests/tests.h"
#include "main.h"
#include "utils/ansi-escape-seqs.h"

int testsRun = 0;

static char *testFoo() {
  muAssert("error, foo != 7", 7 == 7);
  return 0;
}

#include "commands/copy-from-csv.h"
static char *testCopyFromCsv() {
  Table *table;
  loadCsv("stub-data.csv", table);
  muAssert("error loading CSV", true);
  return 0;
}

static char *testSeqScan() {
  char *columns[] = { "title" };
  SeqScanState *state = seqScanInit(&table, columns);
  printf("OK...\n");
  // printf("cmp: %i\n", strcmp(*seqScanNext(state), TABLE_TERMINATOR));
  // printf("cmp: %s\n", *seqScanNext(state));
  seqScanNext(state);
  // A couple problems here. One, the csv is UTF-8, so strcmp is returning garbage.
  // But that should actually be all right... I'm just waiting for TABLE_TERMINATOR.
  // I do wish that there was a cleaner way to return an EOF value. Everything
  // returned from that func has to be the same value, though :/
  // printf("cmp: %i\n", strcmp(*seqScanNext(state), TABLE_TERMINATOR));
  // printf("cmp: %s\n", *seqScanNext(state));
  seqScanNext(state);

  // Another problem: segfault after the third seqScanNext(state). In lldb:
  //  error: Execution was interrupted, reason: EXC_BAD_ACCESS (code=1, address=0x10b71c670).
  //      The process has been returned to the state before expression evaluation.
  // printf("cmp: %i\n", strcmp(*seqScanNext(state), TABLE_TERMINATOR));
  // printf("cmp: %s\n", *seqScanNext(state));
  seqScanNext(state);

  // This will become main.next
  // while (strcmp(*seqScanNext(state), TABLE_TERMINATOR) != 0)
  // printf("state %i", state->currentId);

  printf("numRecords: %i\n", state->currentId);
}

static char *testHashJoin() {
  // TODO: Table is currently a list of strings, make that a list of Records (themselves lists of strings)
  // Below are two initializations for stub Tables made of Records.
  // // posts schema: id, title
  // Table posts = {
  //   {"1", "How do I C"},
  //   {"2", "Why does clang hate me"}
  // };

  // // authors schema: id, postId, name
  // Table authors = {
  //   {"1", "1", "Bert"},
  //   {"2", "1", "Ernie"},
  //   {"3", "2", "Elmo"},
  //   {"4", "3", "The Animal"}
  // };

  // TODO

  return 0;
}

static char *allTests() {
  muRunTest(testFoo);
  muRunTest(testCopyFromCsv);
  return 0;
}



int main(int argc, char **argv) {
  char *result = allTests();
  if (result != 0) {
    printf(ANSI_RED"x"ANSI_RESET" %s\n", result);
  }
  else {
    printf(ANSI_GREEN"%d tests passed\n"ANSI_RESET, testsRun);
  }
  return result != 0;
}
