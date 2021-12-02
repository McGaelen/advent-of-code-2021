#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "../utils.h"

int partA() 
{
  int numIncreases = 0;
  int previousNumber = 0;
  char* fileBuffer;
  char* currentLine;

  read_file("input.txt", &fileBuffer);
  
  // Grab the first number so we exclude it -----------------------
  currentLine = strtok(fileBuffer, "\n");
  previousNumber = atoi(currentLine);

  // Loop through remaining numbers -------------------------------
  while ((currentLine = strtok(NULL, "\n")) != NULL) 
  {
    int currentNumber = atoi(currentLine);

    if (currentNumber > previousNumber)
      numIncreases++;

    previousNumber = currentNumber;
  }

  printf("Number of increase: %i\n", numIncreases);
}

int partB() 
{
  // Create int array containing every number -------------------
  char* fileBuffer;
  int numLines = read_file("input.txt", &fileBuffer);

  int numArray[numLines];
  int index = 0;
  char* currentLine = strtok(fileBuffer, "\n");
  while (currentLine != NULL) 
  {
    int i = atoi(currentLine);
    numArray[index] = i;
    index++;
    currentLine = strtok(NULL, "\n");
  }

  // Iterate through numArray -----------------------------------
  int currentSum = numArray[0] + numArray[1] + numArray[2];
  int previousSum = currentSum;
  int numIncreases = 0;
  index = 1;
  while (index <= (numLines - 3)) // minus 3 for the sliding window
  {
    currentSum = numArray[index] + numArray[index + 1] + numArray[index + 2];
    if (currentSum > previousSum)
      numIncreases++;

    index++;
    previousSum = currentSum;
  }

  printf("Number of increase: %i\n", numIncreases);
}

int main(int argc, char* argv[]) 
{
  char part = *(argv[1]);
  switch (part) {
    case 'a': return partA();
    case 'b': return partB();
  }
}
