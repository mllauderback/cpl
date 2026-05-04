#include <stdio.h>

#include "list.h" // includes token.h

TokenList* token_list_create(int length) {
    TokenList* token_list = malloc(sizeof(TokenList));
    token_list->list = malloc(sizeof(Token*) * length);
    token_list->length = length;
    token_list->num_tokens = 0;
    return token_list;
}

void token_list_free(TokenList* token_list) {
    for (int i = 0; i < token_list->num_tokens; i++) {
        free(token_list->list[i]);
    }
    free(token_list->list);
    free(token_list);
}

void token_list_print(TokenList* token_list) {
    printf("num_tokens: %d\n", token_list->num_tokens);
    for (int i = 0; i < token_list->num_tokens; i++) {
        token_print(token_list->list[i]);
        printf("\n");
    }
}

/**
 * `token` belongs to TokenList - should be malloc'd
 */
void token_list_add(TokenList* token_list, Token* token) {
    if (token_list->num_tokens >= token_list->length) {
        token_list->length *= 1.5;
        token_list->list = realloc(token_list->list, token_list->length);
    }
    token_list->list[token_list->num_tokens] = token;
    token_list->num_tokens++;
}

//void token_list_remove_index(TokenList* list, int index) {
//    // implement if we need it.  deleting just means shifting contents over or setting
//    // the last token to NULL since the list is of token values, not token pointers.
//}
