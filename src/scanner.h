#ifndef CLP_SCANNER_H
#define CLP_SCANNER_H

#include <stdbool.h>

#include "token.h"
#include "utils/list.h"

typedef struct {
    const char* start;
    const char* current;
    int col;
    int line;
} Scanner;

void scanner_init(Scanner* scanner, const char* source);
static bool is_alpha(char c);
static bool is_digit(char c);
bool is_at_end(Scanner* scanner);
char next_char(Scanner* scanner);
char peek(Scanner* scanner);
char peek_next(Scanner* scanner);
char* next_line(const char* source, int* index);
bool match(Scanner* scanner, char expected);

void skip_whitespace(Scanner* scanner);

// token
void token_init(Token* token, TokenType type);
void token_error(Token* token, const char* error_msg);
TokenList* tokenize(Scanner* scanner);

#endif
