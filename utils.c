#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "utils.h"

int read_file( char* filename, char** buffer)
{
  FILE *f;
  struct stat info;

  f = fopen(filename, "r");
  if (f == NULL) {
    perror("read_file error opening file");
    return -1;
  }

  stat(filename, &info);  // store statistics on the file we're opening in the info struct
  char append[info.st_size]; // place to store fgets output

  *buffer = malloc(info.st_size * sizeof(char));
  if (*buffer == NULL) {
    perror("read_file error with malloc()");
    return -1;
  }

  int numLines = 0;
  while ( fgets(append, info.st_size, f) ) // loop while we can read something from fgets.
  {
    numLines++;
    strcat(*buffer, append);
  }

  return numLines;
}

int write_file( char* filename, char* buffer, int size )
{
  FILE *f = fopen(filename, "w");
  if (f == NULL) {
    perror("write_file error opening file");
    return -1;
  }

  // fprintf(f, "%s", buffer);
  fputs(buffer, f);

  return 0;
}