//
// Created by stasi on 08.07.2025.
//

#ifndef OS_STDSTRING_H
#define OS_STDSTRING_H

#include "../../../include/kernel/stdlib/stdbool.h"

int str_count(const char* str);
bool str_compare(char* str1, char* str2);
void str_copy(char* dest, const char* src);
void str_copy_to(char* dest, const char* src, int start_index);
int split_string(char* str, char tokens[][100], int max_tokens);
int int_parse(const char* str);

bool str_contains(const char* haystack, const char* needle);
bool str_starts_with(const char* str, const char* prefix);
bool str_ends_with(const char* str, const char* suffix);

void str_reverse(char* str);
void str_to_upper(char* str);
void str_to_lower(char* str);
void str_concat(char* dest, const char* src);
void int_to_str(int value, char* str);

#endif //OS_STDSTRING_H