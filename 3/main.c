#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "../utils.h"

#define TRUE 1
#define FALSE 0

// #define NUM_DIGITS 5
// #define FILE_NAME "input-example.txt"
#define NUM_DIGITS 12
#define FILE_NAME "input.txt"

int partA() 
{
  char** fileLines;
  // int numLines = read_file_split("input-example.txt", "\n", &fileLines);
  int numLines = read_file_split("input.txt", "\n", &fileLines);

  unsigned int gammaRate = 0;
  for (int currentDigit = 0; currentDigit < NUM_DIGITS; currentDigit++) 
  {
    int numZeroes = 0;
    int numOnes = 0;
    for (int currentLine = 0; currentLine < numLines; currentLine++)
    {
      char c = fileLines[currentLine][currentDigit];
      (c == '0') ? numZeroes++ : numOnes++;
    }

    gammaRate = gammaRate << 1;
    if (numOnes > numZeroes)
      gammaRate = gammaRate | 1;
  }

  unsigned int epsilonRate = ~gammaRate;

  // get rid of all the 1's in front caused by the inversion.
  // we only want a 12 bit number (or 5 bits for the example data)
  // epsilonRate = epsilonRate & 0x0000001f;
  epsilonRate = epsilonRate & 0x00000fff;

  printf("Final rates: %i gamma rate, %i epsilonRate = %u product\n", gammaRate, epsilonRate, gammaRate * epsilonRate);
}



/*
 * returns the final number if done, otherwise returns FALSE
 */
long int checkDone(char*** a, size_t size)
{
  char** ary = *a;

  int numDeletions = 0;
  char* lastNumber;
  for (int i = 0; i < size; i++)
  {
    if (ary[i] == "x") 
      numDeletions++;
    else
      lastNumber = ary[i];
  }

  if (numDeletions == (size - 1))
    return strtol(lastNumber, NULL, 2);
  return FALSE;
}

int partB() 
{
  char** fileLines;

  /*
    Oxygen -----------------------------------------------------------------
  */
  // int numLines = read_file_split("input-example.txt", "\n", &fileLines);
  int numLines = read_file_split(FILE_NAME, "\n", &fileLines);
  long int oxygen = 0;
  for (int currentDigit = 0; currentDigit < NUM_DIGITS; currentDigit++) 
  {
    // Figure out what's more common -------------------------------
    int onesMoreCommon = FALSE;
    int numZeroes = 0;
    int numOnes = 0;
    for (int currentLine = 0; currentLine < numLines; currentLine++)
    {
      char c = fileLines[currentLine][currentDigit];
      if (strcmp(fileLines[currentLine], "x") == 0) continue;

      (c == '0') ? numZeroes++ : numOnes++;
    }

    if (numOnes >= numZeroes)
      onesMoreCommon = TRUE;


    // Remove entries that don't match criteria --------------------
    for (int currentLine = 0; currentLine < numLines; currentLine++)
    {
      char c = fileLines[currentLine][currentDigit];
      if (strcmp(fileLines[currentLine], "x") == 0) continue;

      if ((onesMoreCommon == TRUE && c == '0') || 
          (onesMoreCommon == FALSE && c == '1')) 
      {
        fileLines[currentLine] = "x";
      }
    }

    oxygen = checkDone(&fileLines, numLines);
    if (oxygen > 0)
      break;

  }


  /*
    CO2 -----------------------------------------------------------------
  */
  free(fileLines);
  // char** fileLines;
  read_file_split(FILE_NAME, "\n", &fileLines);
  // int numLines = read_file_split("input.txt", "\n", &fileLines);
  long int co2 = 0;
  for (int currentDigit = 0; currentDigit < NUM_DIGITS; currentDigit++) 
  {
    // Figure out what's more common -------------------------------
    int onesMoreCommon = FALSE;
    int numZeroes = 0;
    int numOnes = 0;
    for (int currentLine = 0; currentLine < numLines; currentLine++)
    {
      char c = fileLines[currentLine][currentDigit];
      if (strcmp(fileLines[currentLine], "x") == 0) continue;

      (c == '0') ? numZeroes++ : numOnes++;
    }

    if (numOnes >= numZeroes)
      onesMoreCommon = TRUE;


    // Remove entries that don't match criteria --------------------
    for (int currentLine = 0; currentLine < numLines; currentLine++)
    {
      printf("%s\n", fileLines[currentLine]);
      char c = fileLines[currentLine][currentDigit];
      if (strcmp(fileLines[currentLine], "x") == 0) continue;

      if ((onesMoreCommon == TRUE && c == '1') || 
          (onesMoreCommon == FALSE && c == '0')) 
      {
        fileLines[currentLine] = "x";
      }

    }
    printf("\n");

    co2 = checkDone(&fileLines, numLines);
    if (co2 > 0)
      break;

  }

  printf("oxygen: %li\n", oxygen);
  printf("co2: %li\n", co2);

  printf("result: %li\n", oxygen * co2);
}



int main(int argc, char* argv[])
{
  char part = *(argv[1]);
  switch (part) {
    case 'a': return partA();
    case 'b': return partB();
  }
}