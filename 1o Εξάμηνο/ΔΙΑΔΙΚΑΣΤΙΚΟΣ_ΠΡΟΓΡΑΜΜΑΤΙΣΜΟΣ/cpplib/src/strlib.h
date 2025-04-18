#ifndef _strlib_h
#define _strlib_h

#include "genlib.h"

string Concat(string s1, string s2);

char IthChar(string s, int i);

string SubString(string s, int p1, int p2);

string CharToString(char ch);

int StringLength(string s);

string CopyString(string s);

bool StringEqual(string s1, string s2);

int StringCompare(string s1, string s2);

int FindChar(char ch, string text, int start);

string ConvertToLowerCase(string s);

string ConvertToUpperCase(string s);

string IntegerToString(int n);

int StringToInteger(string s);

string RealToString(double d);

double StringToReal(string s);

#endif

		
