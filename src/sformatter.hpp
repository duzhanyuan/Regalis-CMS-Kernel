/*
 *
 * Copyright 2011 Patryk Jaworski <skorpion9312@gmail.com>
 * License: GNU GPLv3
 *
*/
#ifndef _SFORMATTER_HPP
#define _SFORMATTER_HPP
#include <string>
using std::string;

string& operator%(string& str, const string& replace);
string& operator%(string& str, const int* replace);
string& operator%(string& str, int replace);
string& operator%(string& str, const long long unsigned int* replace);
string& operator%(string& str, long long unsigned int replace);
string& operator%(string& str, const char* replace);
string operator%(string str, const string& replace);

#endif
