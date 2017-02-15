#include <stdio.h>
#include "tests.h"
#include "../utils/terminal-utils.h"

int tests_run = 0;

static char *test_foo() {
  mu_assert("error, foo != 7", 7 == 7);
  return 0;
}

static char *all_tests() {
  mu_run_test(test_foo);
  return 0;
}

int main(int argc, char **argv) {
  char *result = all_tests();
  if (result != 0) {
    printf(ANSI_RED"x"ANSI_RESET" %s\n", result);
  }
  else {
    printf(ANSI_GREEN"%d tests passed\n"ANSI_RESET, tests_run);
  }
  return result != 0;
}
