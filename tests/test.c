#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "main/main.h"
#include "executor/seq-scan.h"
#include "utils/ansi-escape-seqs.h"
#include "utils/utils.h"
#include "tests/tests.h"

int testsRun = 0;

#include "commands/load-csv.h"

static char *testCopyFromCsv() {
  Table *table = (Table *) calloc(MAX_RECORDS, MAX_RECORD_SIZE);
  loadCsv("tests/stub-data.csv", table);
  muAssert("CSV line 0", strcmp((*table)[0]->documentNumber, "CIA-RDP73-00402R000100290030-0") == 0);
  muAssert("CSV line 1", strcmp((*table)[1]->documentCreationDate, "2016-12-12") == 0);
  muAssert("CSV line 2", strcmp((*table)[2]->url, "https://www.cia.gov/library/readingroom/document/cia-rdp80b01676r001700050006-5") == 0);
  free(table);
  return 0;
}

/* static char *testSeqScan() { */
  /* Table *table; */
  /* SeqScanState *state = seqScanInit(table, 10); */
  /* seqScanNext(state); */
  /* // while (strcmp(*seqScanNext(state), TABLE_TERMINATOR) != 0) */
    /* // printf("state %i", state->currentId); */
  /* // printf("numRecords: %i\n", state->position); */

  /* // TODO: test last returned record, maybe? */
  /* return 0; */
/* } */

static char *testStrtokWithBlank(){
  char a[] = "hi,world,,bye";
  char *next;
  char comma = ',';

  next = strtokWithBlank(a, &comma);
  // strcmp returns lexical distance, 0 means they're equal.
  muAssert("First item should be hi was\n", strcmp(next, "hi") == 0);
  next = strtokWithBlank(NULL, &comma);
  muAssert("Second item should be world", strcmp(next, "world") == 0);
  next = strtokWithBlank(NULL, &comma);
  muAssert("Third item should be ''", strcmp(next, "") == 0);
  next = strtokWithBlank(NULL, &comma);
  muAssert("Fourth item should be bye", strcmp(next, "bye") == 0);

  return 0;
}

static char *testHashJoin() {
  // TODO: Table is currently a list of strings, we'll need to make that into a list of Records (themselves lists of strings?).
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
  muRunTest(testCopyFromCsv);
  muRunTest(testStrtokWithBlank);
  /* muRunTest(testSeqScan); */
  /* muRunTest(testHashJoin); */
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
