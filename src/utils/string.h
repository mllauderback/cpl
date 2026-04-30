#ifndef CPL_UTILS_STRING_H
#define CPL_UTILS_STRING_H

#include <stdlib.h>

typedef struct {
    size_t size;
    size_t length;
    char* buffer;
} StringBuffer;

void sb_init(StringBuffer* buffer, int size);
void sb_free(StringBuffer* buffer);
void sb_append(StringBuffer* buffer, char c);
void sb_clear(StringBuffer* buffer);

#endif
