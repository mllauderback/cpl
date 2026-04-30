#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "string.h"

void sb_init(StringBuffer* buffer, int size) {
    buffer->size = size;
    buffer->length = 0;
    buffer->buffer = malloc(sizeof(char) * size);
}

void sb_free(StringBuffer* buffer) {
    free(buffer->buffer);
}

void sb_append(StringBuffer* buffer, char c) {
    if (buffer->length == buffer->size) {
        buffer->size *= 1.5;
        buffer->buffer = realloc(buffer->buffer, buffer->size);
    }
    buffer->buffer[buffer->length++] = c;
}

// dest should be length+1
void sb_string(StringBuffer* buffer, char* dest) {
    if (strlen(dest) < buffer->length + 1) {
        fprintf(stderr, "From: sb_string: dest: not enough memory allocated.");
        exit(EXIT_FAILURE);
    }
    strncpy(buffer->buffer, dest, buffer->length);
    dest[buffer->length + 1] = '\0'; // null terminate
}

void sb_clear(StringBuffer* buffer) {
    memset(buffer->buffer, 0, buffer->size);
    buffer->length = 0;
}
