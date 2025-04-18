#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>

#include "genlib.h"

#define ErrorExitStatus 1

char undefined_object[] = "UNDEFINED";

void *GetBlock(size_t nbytes)
{
  void *result;

  result = malloc(nbytes);
  if (result == NULL) Error("No memory available");
  return (result);
}

void FreeBlock(void *ptr)
{
  free(ptr);
}


void Error(string msg, ...)
{
  va_list args;

  va_start(args, msg);
  fprintf(stderr, "Error: ");
  vfprintf(stderr, msg, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(ErrorExitStatus);
}
