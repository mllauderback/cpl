#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "scanner.h" // includes token.h and list.h
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

const char* next_char(Scanner* scanner) {
    scanner->current++;
    scanner->col++;
    char next = scanner->current[-1];
    if (next == '\n') {
        scanner->col = 0;
        scanner->line++;
    }
    return &scanner->current[-1];
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
TokenList* tokenize(Scanner* scanner, const char* filename) {

    TokenList* token_list = token_list_create(100);
    Token* token;

    // single-character tokens
    while (!is_at_end(scanner)) {
        skip_whitespace(scanner); // CPL is whitespace insensitive.
        // edge case where whitespace pads the end of the file
        if (is_at_end(scanner)) return token_list;

        const char* c = next_char(scanner);
        switch (*c) {
            case '(':
                token = token_create(TOKEN_LEFT_PAREN, c, 1, scanner->line);
                token_list_add(token_list, token);
                continue;
            case ')':
                token = token_create(TOKEN_RIGHT_PAREN, c, 1, scanner->line);
                token_list_add(token_list, token);
                continue;
            case '[':
                token = token_create(TOKEN_LEFT_BRACKET, c, 1, scanner->line);
                token_list_add(token_list, token);
                continue;
            case ']':
                token = token_create(TOKEN_RIGHT_BRACKET, c, 1, scanner->line);
                token_list_add(token_list, token);
                continue;
            case ',':
                token = token_create(TOKEN_COMMA, c, 1, scanner->line);
                token_list_add(token_list, token);
                continue;
            case '.':
                token = token_create(TOKEN_DOT, c, 1, scanner->line);
                token_list_add(token_list, token);
                continue;
            case ';':
                token = token_create(TOKEN_SEMICOLON, c, 1, scanner->line);
                token_list_add(token_list, token);
                continue;
            case '{':
                token = token_create(TOKEN_LEFT_BRACE, c, 1, scanner->line);
                token_list_add(token_list, token);
                continue;
            case '}':
                token = token_create(TOKEN_RIGHT_BRACE, c, 1, scanner->line);
                token_list_add(token_list, token);
                continue;
        }
    }
    return token_list;
}

