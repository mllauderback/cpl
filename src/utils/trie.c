#include <string.h>
#include <stdio.h>

#include "trie.h" // includes stdlib and stdbool

bool _lexeme_trie_node_has_no_children(LexemeTrieNode* node) {
    for (size_t i = 0; i < TRIE_NUM_CHARS; i++) {
        if (node->children[i] != NULL) return false;
    }
    return true;
}

/**
 * LexemeTrieNode takes ownership of itself, an its children LexemeTrieNodes
 */
LexemeTrieNode* lexeme_trie_node_create() {
    LexemeTrieNode* root = malloc(sizeof(LexemeTrieNode));
    for (int i = 0; i < TRIE_NUM_CHARS; i++) {
        root->children[i] = NULL;
    }
    root->is_terminal = false;
    return root;
}

void _lexeme_trie_node_children_free(LexemeTrieNode* node) {
   for (int i = 0; i < TRIE_NUM_CHARS; i++) {
       if (node->children[i] != NULL) {
           _lexeme_trie_node_children_free(node->children[i]);
       }
   }
   free(node);
}

void lexeme_trie_node_free(LexemeTrieNode* root) {
    _lexeme_trie_node_children_free(root);
}

void lexeme_trie_node_add(LexemeTrieNode* root, const char* lexeme) {
    size_t lexeme_len = strlen(lexeme);
    LexemeTrieNode* current = root;

    for (size_t i = 0; i < lexeme_len; i++) {
        unsigned char char_index = (unsigned char)lexeme[i];
        if (current->children[char_index] == NULL) {
            current->children[char_index] = lexeme_trie_node_create();
        }
        current = current->children[char_index];
    }
    current->is_terminal = true;
}

/**
 * Returns true if the lexeme string is found, false otherwise.
 */
bool lexeme_trie_node_search(LexemeTrieNode* root, const char* lexeme) {
    size_t lexeme_len = strlen(lexeme);
    LexemeTrieNode* current = root;
    for (size_t i = 0; i < lexeme_len; i++) {
        unsigned char char_index = (unsigned char)lexeme[i];
        if (current->children[char_index] == NULL) return false;
        current = current->children[char_index];
    }
    return current->is_terminal;
}

void _lexeme_trie_node_print_rec(LexemeTrieNode* node, unsigned char* prefix, size_t length) {
    unsigned char new_prefix[length + 2];
    memcpy(new_prefix, prefix, length);
    new_prefix[length + 1] = 0;

    if (node->is_terminal) {
        printf("%s\n", prefix);
    }

    for (size_t i = 0; i < TRIE_NUM_CHARS; i++) {
        if (node->children[i] != NULL) {
            new_prefix[length] = i;
            _lexeme_trie_node_print_rec(node->children[i], new_prefix, length + 1);
        }
    }
}

/**
 * Prints list of lexemes in the trie starting at root.
 */
void lexeme_trie_node_print(LexemeTrieNode* root) {
    if (root == NULL || _lexeme_trie_node_has_no_children(root)) {
        printf("Trie is empty!\n");
        return;
    }
    _lexeme_trie_node_print_rec(root, NULL, 0);
}
