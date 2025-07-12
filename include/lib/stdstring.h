//
// Created by stasi on 08.07.2025.
//

#ifndef OS_STDSTRING_H
#define OS_STDSTRING_H

#include "stdbool.h"

int str_count(char* str);
bool str_compare(char* str1, char* str2);
void str_copy(char* dest, const char* src);
int split_string(char* str, char tokens[][100], int max_tokens);
int int_parse(const char* str);

#endif //OS_STDSTRING_H