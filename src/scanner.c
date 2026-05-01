#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "scanner.h"
#include "utils/error.h"

void substr(const char* source, char* dest, int start, size_t length) {
    for (size_t i = 0; i < length; i++) {
        dest[i] = source[start + i];
    }
    dest[length] = '\0';
}

static bool is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

void scanner_init(Scanner* scanner, const char* source) {
    scanner->start = source;
    scanner->current = source;
    scanner->col = 0;
    scanner->line = 0;
}

bool is_at_end(Scanner* scanner) {
    return *scanner->current == '\0';
}

char next_char(Scanner* scanner) {
    scanner->current++;
    scanner->col++;
    return scanner->current[-1];
}

char peek_next(Scanner* scanner) {
    if (is_at_end(scanner)) {
        return '\0';
    }
    return scanner->current[1];
}

char peek(Scanner* scanner) {
    return *scanner->current;
}

void skip_whitespace(Scanner* scanner) {
    while (*scanner->current == ' ') {
        next_char(scanner);
    }
}

//char* next_line(const char* source, int* index) {
//    int start = *index;
//    while (source[*index] != '\n') {
//        (*index)++;
//    }
//    size_t length = *index - start;
//    char* line = malloc(sizeof(char) * length);
//    substr(source, line, start, length);
//    (*index)++;
//
//    return line;
//}

/* Tokens */
void token_init(Token* token, TokenType type) {
    token->type = type;
    token->start = NULL;
    token->length = 0;
    token->line = 0;
}

TokenList* tokenize(Scanner* scanner, const char* filename) {

    TokenList* token_list = token_list_create(100);

//    while (!is_at_end(scanner)) {
        skip_whitespace(scanner); // CPL is whitespace insensitive.
        // edge case where whitespace pads the end of the file
        if (is_at_end(scanner)) return token_list;

        char c = peek(scanner);
        if(!is_alpha(c)) {
            // invalid statement
            throw_error(
                    CPL_ERROR_INVALID_STATEMENT,
                    CPL_ERROR_INVALID_VARIABLE_START,
                    filename,
                    scanner->line,
                    scanner->col);
        }
//    }

    return token_list;
}

