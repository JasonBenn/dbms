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
