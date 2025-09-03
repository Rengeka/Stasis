//
// Created by stasi on 08.07.2025.
//

#include "../../../include/kernel/stdlib/stdbool.h"

int str_count(const char* str)
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

void str_copy_to(char* dest, const char* src, int start_index) {
    int i = 0;
    while (src[i] != '\0') {
        dest[start_index + i] = src[i];
        i++;
    }
    dest[start_index + i] = '\0';
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

bool str_contains(const char* haystack, const char* needle) {
    if (*needle == '\0') return true;

    for (int i = 0; haystack[i] != '\0'; i++) {
        int j = 0;
        while (haystack[i + j] == needle[j] && needle[j] != '\0') {
            j++;
        }
        if (needle[j] == '\0') {
            return true;
        }
    }

    return false;
}

bool str_starts_with(const char* str, const char* prefix) {
    while (*prefix) {
        if (*str != *prefix) return false;
        str++;
        prefix++;
    }
    return true;
}

bool str_ends_with(const char* str, const char* suffix) {
    int len_str = str_count(str);
    int len_suffix = str_count(suffix);

    if (len_suffix > len_str) return false;

    for (int i = 0; i < len_suffix; i++) {
        if (str[len_str - len_suffix + i] != suffix[i]) {
            return false;
        }
    }

    return true;
}

void str_reverse(char* str) {
    int len = str_count(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}


void str_to_upper(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
}

void str_concat(char* dest, const char* src) {
    int dest_len = str_count(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
}

void int_to_str(int value, char* str) {
    int i = 0;
    bool is_negative = false;

    if (value == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (value < 0) {
        is_negative = true;
        value = -value;
    }

    while (value != 0) {
        int digit = value % 10;
        str[i++] = (char)(digit + '0');
        value /= 10;
    }

    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}