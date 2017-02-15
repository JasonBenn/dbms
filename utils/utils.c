void chomp(char *str) {
  // Remove newline or carriage return char from end of string.
  int end = strlen(str) - 1;
  if (str[end] == '\n' || str[end] == '\r')
    str[end] = '\0';
}

void getInput(char *input) {
  // TODO: reject invalid input.
  printf("query: ");
  fgets(input, MAX_INPUT, stdin);
}
