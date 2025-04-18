#include <stdio.h>
#include <string.h>
#include "genlib.h"
#include "strlib.h"
#include "simpio.h"

#define InitialBufferSize 120

int GetInteger(void)
{
  string line;
  int value;
  char termch;

  while (TRUE) {
    line = GetLine();
    switch (sscanf(line, " %d %c", &value, &termch)){
      case 1:
	FreeBlock(line);
	return (value);
      case 2:
	printf("Unexpected character: '%c'\n", termch);
	break;
    default:
        printf("Please enter an interget\n");
        break;
    }
      FreeBlock(line);
      printf("Retry: ");
      }
  }
long GetLong(void)
{
  string line;
  long value;
  char termch;

  while(TRUE){
    line = GetLine();
    switch (sscanf(line, " %ld %c", &value, &termch)){
      case 1:
	FreeBlock(line);
	return (value);
    case 2:
      printf("Unexpected character: '%c'\n", termch);
      break;
    default:
      printf("Please enter an integer\n");
      break;
    }
    FreeBlock(line);
    printf("Retry: ");
  }
}

double GetReal(void)
{
  string line;
  double value;
  char termch;

  while (TRUE) {
    line = GetLine();
    switch (sscanf(line, " %lf %c", &value, &termch)) {
      case 1:
	FreeBlock(line);
	return (value);
      case 2:
        printf("Unexpected character: '%c'\n", termch);
	break;
      default:
	printf("Please enter a real number\n");
	break;
    }
    FreeBlock(line);
    printf("Retry: ");
  }
}

string GetLine(void)
{
  return (ReadLine(stdin));
}

string ReadLine(FILE*infile)
{
  string line, nline;
  int n, ch, size;

  n = 0;
  size = InitialBufferSize;
  line = GetBlock(size + 1);
  while ((ch = getc(infile)) != '\n' && ch != EOF){
    if(n == size) {
      size *= 2;
      nline = (string) GetBlock(size + 1);
      strncpy(nline, line, n);
      FreeBlock(line);
      line = nline;
    }
    line[n++] = ch;
  }
  if (n == 0 && ch == EOF){
    FreeBlock(line);
    return (NULL);
  }
  line[n] = '\0';
  nline = (string) GetBlock(n + 1);
  strcpy(nline, line);
  FreeBlock(line);
  return (nline);
}
