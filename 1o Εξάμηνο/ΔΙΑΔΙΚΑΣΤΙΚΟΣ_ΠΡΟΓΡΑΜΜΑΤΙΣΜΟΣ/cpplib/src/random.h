#ifndef _random_h
#define _random_h

#include "genlib.h"


void Randomize(void);

int RandomInteger(int low, int high);

double RandomReal(double low, double high);

bool RandomChance(double p);

#endif
