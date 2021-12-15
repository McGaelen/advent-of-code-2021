#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "utils.h"

int read_file(char* filename, char** buffer)
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

int read_file_split(char* filename, char* delimiter, char*** outBuffer)
{
  // Load entire file into memory --------------------------------------
  FILE* f = fopen(filename, "r");

  struct stat info;
  stat(filename, &info);  // store statistics on the file we're opening in the info struct

  char append[info.st_size]; // place to store fgets output
  char* buffer = malloc(info.st_size * sizeof(char));

  int numLines = 0;
  while ( fgets(append, info.st_size, f) ) // loop while we can read something from fgets.
  {
    numLines++;
    strcat(buffer, append);
  }

  // Split up string by delimiter into individual char*'s --------------
  *outBuffer = malloc(sizeof(char*) * numLines);

  *outBuffer[0] = strtok(buffer, delimiter); 
  for (int i = 1; i < numLines; i++) {
    (*outBuffer)[i] = strtok(NULL, delimiter); 
  }

  // outBuffer = outBuffer;
  return numLines;
}

int write_file(char* filename, char* buffer, int size)
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