#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "scanner.h"

void substr(const char* source, char* dest, int start, size_t length) {
    for (size_t i = 0; i < length; i++) {
        dest[i] = source[start + i];
    }
    dest[length] = '\0';
}

bool is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool is_at_end(char* char_ptr) {
    return *char_ptr == '\0';
}

char next_char(char* char_ptr) {
    char_ptr++;
    return char_ptr[-1];
}

char peek_next(char* char_ptr) {
    if (is_at_end(char_ptr)) {
        return '\0';
    }
    return char_ptr[1];
}

char* next_line(const char* source, int* index) {
    int start = *index;
    while (source[*index] != '\n') {
        (*index)++;
    }
    size_t length = *index - start;
    char* line = malloc(sizeof(char) * length);
    substr(source, line, start, length);
    (*index)++;

    return line;
}
