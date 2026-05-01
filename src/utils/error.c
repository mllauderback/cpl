#include <string.h>

#include "error.h"

#define COLOR_RED    "\033[31m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define RESET        "\033[0m"

void throw_error(char* msg_type, char* msg_description, const char* file, int line, int col) {
    if (file == NULL) { // no file means no line or column
        fprintf(stderr, COLOR_RED "%s: %s." RESET "\n", msg_type, msg_description);
    } else {
        fprintf(stderr,
                COLOR_RED "%s: %s\n\tin: %s; Line %d, col %d." RESET "\n",
                msg_type, msg_description, file, line, col);
    }
    exit(EXIT_FAILURE);
}

void throw_warning(char* msg_type, char* msg_description, const char* file, int line, int col) {
    if (file == NULL) { // no file means no line or column
        fprintf(stderr, COLOR_YELLOW "%s: %s." RESET "\n", msg_type, msg_description);
    } else {
        fprintf(stderr,
                COLOR_YELLOW "%s: %s\n\tin: %s; Line %d, col %d." RESET "\n",
                msg_type, msg_description, file, line, col);
    }
}
