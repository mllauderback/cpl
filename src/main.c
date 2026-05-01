#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scanner.h"
#include "utils/error.h"

int str_ends_with(const char* str, const char* suffix) {
    if (!str || !suffix) {
        return 0;
    }
    size_t len_str = strlen(str);
    size_t len_suffix = strlen(suffix);
    if (len_suffix > len_str) {
        return 0;
    }
    return strncmp(str + len_str - len_suffix, suffix, len_suffix) == 0;
}

static char* read_file(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
//        fprintf(stderr, "Could not open file \"%s\".\n", path);
//        exit(74);
        throw_error(CPL_ERROR_FILE_READ, CPL_ERROR_CANNOT_OPEN_FILE, NULL, 0, 0);
    }
    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char* buffer = malloc(file_size + 1);
    if (buffer == NULL) {
//        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
//        exit(74);
        throw_error(CPL_ERROR_FILE_READ, CPL_ERROR_INSUFFICIENT_RAM, NULL, 0, 0);
    }
    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    if (bytes_read < file_size) {
//        fprintf(stderr, "Could not read file \"%s\".\n", path);
//        exit(74);
        throw_error(CPL_ERROR_FILE_READ, CPL_ERROR_CANNOT_READ_FILE, NULL, 0, 0);
    }
    buffer[bytes_read] = '\0';

    fclose(file);
    return buffer;
}

static void run_file(const char* path) {
    // malloc'd - source needs to last the entire lifetime of the compilation
    // process
    char* source = read_file(path);
//    int source_len = strlen(source);
//
//    int index = 0;
//    int line_no = 0;
//    while (index < source_len) {
//        char* line = next_line(source, &index);
//        printf("line %d: %s\n", line_no, line);
//        line_no++;
//        free(line);
//    }
    Scanner scanner;
    scanner_init(&scanner, source);

    TokenList* token_list = tokenize(&scanner, path);

    token_list_free(token_list);
    free(source);
}

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        throw_error(CPL_ERROR_INCORRECT_USAGE, CPL_ERROR_MUST_INCLUDE_SOURCE,
                NULL, 0, 0);
        return EXIT_FAILURE;
    }
    if (str_ends_with(argv[1], ".cpl") == 0) {
        throw_error(CPL_ERROR_INCORRECT_USAGE, CPL_ERROR_SOURCE_WRONG_EXT,
                NULL, 0, 0);
        return EXIT_FAILURE;
    }

    run_file(argv[1]);

    return EXIT_SUCCESS;
}
