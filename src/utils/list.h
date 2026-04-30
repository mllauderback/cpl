#ifndef CLP_LIST_H
#define CLP_LIST_H

#include "../token.h"

typedef struct {
    int length;
    int num_tokens;
    Token* list;
} TokenList;

TokenList* token_list_create(int length);
void token_list_free(TokenList* list);
void token_list_add(TokenList* list, Token token); 
//void token_list_remove_index(TokenList* list, int index);
//void token_list_remove_token(TokenList* list, Token* token);

#endif
