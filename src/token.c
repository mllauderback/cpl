#include <string.h>
#include <stdio.h>

#include "token.h"

// must be updated in the right order when tokens are added to TokenType
const char* const token_type_map[_TOKEN_TYPE_LENGTH] = {
    "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE",
    "RIGHT_BRACE", "COMMA", "DOT",
    "SEMICOLON", "LEFT_BRACKET", "RIGHT_BRACKET",
    "LESS", "GREATER", "LESS_LESS", "GREATER_GREATER",
    "PLUS", "PLUS_PLUS", "MINUS", "MINUS_MINUS", "STAR",
    "STAR_STAR", "FSLASH", "FSLASH_FSLASH",
    "FSLASH_STAR", "STAR_FSLASH", "BANG",
    "BANG_EQUAL", "EQUAL", "EQUAL_EQUAL", "LESS_EQUAL",
    "GREATER_EQUAL", "MINUS_EQUAL", "PLUS_EQUAL",
    "STAR_EQUAL", "FSLASH_EQUAL", "PERCENT", "PERCENT_EQUAL",
    "STAR_STAR_EQUAL", "LESS_LESS_EQUAL", "PIPE", "AMP",
    "GREATER_GREATER_EQUAL", "AMP_EQUAL", "PIPE_EQUAL",
    "CARET", "CARET_EQUAL", "TILDE", "TILDE_EQUAL",
    "IDENTIFIER", "STRING", "NUMBER",
    "CHARACTER", "DEF", "CLASS", "PUBLIC", "PRIVATE",
    "PROTECTED", "IMPLEMENTS", "STATIC",
    "UNDEFINED", "TRUE", "FALSE", "MODULE",
    "IF", "ELSE", "FOR", "WHILE", "AND",
    "OR", "XOR", "RETURN", "SUPER", "THIS",
    "NEW", "IS", "ERROR", "EOF",
};

// eventually add rest of fields to constructor
Token* token_create(TokenType type, const char* start, size_t length, int line) {
    Token* token = malloc(sizeof(Token));
    token->type = type;
    token->start = start;
    token->length = length;
    token->line = line;
    return token;
}

void token_print(Token* token) {
    char token_str[token->length + 1];
    strncpy(token_str, token->start, token->length);
    token_str[token->length] = '\0';
    printf("%s (\"%s\")", token_type_map[token->type], token_str);
}
