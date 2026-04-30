#include "list.h"

TokenList* token_list_create(int length) {
    TokenList* token_list = malloc(sizeof(TokenList));
    token_list->list = malloc(sizeof(Token) * length);
    token_list->length = length;
    token_list->num_tokens = 0;
    return token_list;
}

void token_list_free(TokenList* token_list) {
    free(token_list->list);
    free(token_list);
}

void token_list_add(TokenList* token_list, Token token) {
    if (token_list->num_tokens == token_list->length) {
        token_list->length *= 1.5;
        token_list->list = realloc(token_list->list, token_list->length);
    }
    token_list->list[token_list->num_tokens++] = token;
}

//void token_list_remove_index(TokenList* list, int index) {
//    // implement if we need it.  deleting just means shifting contents over or setting
//    // the last token to NULL since the list is of token values, not token pointers.
//}
