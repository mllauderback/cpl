#include "token.h"

void token_init(Token* token, enum token_type type, char* lexeme, char* start, size_t length, int line) {
    token->type = type;
    token->lexeme = lexeme;
    token->start = start;
    token->length = length;
    token->line = line;
}
