#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "../utils.h"

int partA() 
{
  int horizontal = 0;
  int depth = 0;
  char** fileLines;

  int numLines = read_file_split("input.txt", "\n", &fileLines);

  char direction;
  int amount;
  for (int i = 0; i < numLines; i++) 
  {
    direction = strtok(fileLines[i], " ")[0];
    amount = atoi(strtok(NULL, "\0"));

    switch (direction) {
      case 'f':
        horizontal += amount; break;
      case 'd':
        depth += amount; break;
      case 'u':
        depth -= amount; break;
    }
  }

  printf("Final position: %i horizontal, %i depth = %i product\n", horizontal, depth, horizontal * depth);
}



int partB() 
{
  int horizontal = 0;
  int depth = 0;
  int aim = 0;
  char** fileLines;

  int numLines = read_file_split("input.txt", "\n", &fileLines);

  char direction;
  int amount;
  for (int i = 0; i < numLines; i++) 
  {
    direction = strtok(fileLines[i], " ")[0];
    amount = atoi(strtok(NULL, "\0"));

    switch (direction) {
      case 'f':
        horizontal += amount;
        depth += (aim * amount);
        break;
      case 'd':
        aim += amount; 
        break;
      case 'u':
        aim -= amount; 
        break;
    }
  }

  printf("Final position: %i horizontal, %i depth = %i product\n", horizontal, depth, horizontal * depth);
}

int main(int argc, char* argv[]) 
{
  char part = *(argv[1]);
  switch (part) {
    case 'a': return partA();
    case 'b': return partB();
  }
}
