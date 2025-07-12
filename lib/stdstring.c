//
// Created by stasi on 08.07.2025.
//

#include "../include/lib/stdbool.h"

int str_count(char* str)
{
    int count = 0;
    while (str[count] != '\0') {
        count++;
    }
    return count;
}

bool str_compare(char* str1, char* str2)
{
    if (str_count(str1) != str_count(str2)) {
        return false;
    }

    int i = 0;
    while (str1[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }

    return true;
}

void str_copy(char* dest, const char* src)
{
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int split_string(char* str, char tokens[][100], int max_tokens) {
    int count = 0;
    char* p = str;
    while (*p != '\0' && count < max_tokens) {
        while (*p == ' ') p++;
        if (*p == '\0') break;

        int i = 0;
        while (*p != ' ' && *p != '\0' && i < 99) {
            tokens[count][i++] = *p++;
        }
        tokens[count][i] = '\0';
        count++;
    }
    return count;
}

int int_parse(const char* str) {
    int res = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') break;
        res = res * 10 + (str[i] - '0');
    }
    return sign * res;
}

