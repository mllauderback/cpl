#ifndef CPL_TRIE_H
#define CPL_TRIE_H

#include <stdlib.h>
#include <stdbool.h>

#define TRIE_NUM_CHARS 256

typedef struct LexemeTrieNode {
    struct LexemeTrieNode* children[TRIE_NUM_CHARS];
    bool is_terminal;
} LexemeTrieNode;

LexemeTrieNode* lexeme_trie_node_create();
void lexeme_trie_node_free(LexemeTrieNode* root);
void lexeme_trie_node_add(LexemeTrieNode* root, const char* lexeme);
bool lexeme_trie_node_search(LexemeTrieNode* root, const char* lexeme);
void lexeme_trie_node_print(LexemeTrieNode* root);
// add delete and modify later = shouldn't need this since the tree is const

#endif
