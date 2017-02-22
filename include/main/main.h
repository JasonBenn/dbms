#define MAX_RECORDS 64000
#define MAX_RECORD_SIZE 1500

#ifndef RECORD
#define RECORD
typedef struct {
  char *documentNumber;
  char *documentCreationDate;
  char *documentReleaseDate;
  char *title;
  char *url;
} Record;
#endif

typedef Record *(Table[25]);
