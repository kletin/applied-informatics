#ifndef _genlib_h
#define _genlib_h

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


#ifdef THINK_C
   typedef int bool;
#else
#  ifdef TRUE
#    ifndef bool
#      define bool int
#    endif
#   else
#   ifdef bool
#     define FALSE 0
#     define TRUE 1
#   else
      typedef enum {FALSE, TRUE} bool;
#   endif
#  endif
# endif



typedef char *string;


#define UNDEFINED ((void*) undefined_object)

extern char undefined_object[];


void *GetBlock(size_t nbytes);

void FreeBlock(void *ptr);

#define NewArray(n, type)  ((type *) GetBlock((n)*sizeof(type)))

void Error(string msg, ...);

#endif

