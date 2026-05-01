#ifndef CPL_ERROR_H
#define CPL_ERROR_H

#include <stdio.h>

#include "../scanner.h"

// error message types
#define CPL_ERROR_FILE_READ "Error reading file"
#define CPL_ERROR_INCORRECT_USAGE "Incorrect usage"
#define CPL_ERROR_INVALID_STATEMENT "Invalid statement"

// error message descriptions
#define CPL_ERROR_MUST_INCLUDE_SOURCE "Must include source file to compile"
#define CPL_ERROR_CANNOT_OPEN_FILE "Cannot open file"
#define CPL_ERROR_INSUFFICIENT_RAM "Not enough memory"
#define CPL_ERROR_CANNOT_READ_FILE "Cannot read file"
#define CPL_ERROR_SOURCE_WRONG_EXT "Source file must be '.cpl'"

#define CPL_ERROR_INVALID_VARIABLE_START "Variable cannot start with"
#define CPL_ERROR_INVALID_VARIABLE_CONTAINS "Variable cannot contain"
#define CPL_ERROR_INVALID_VARIABLE_RESERVED "Variable cannot be a reserved keyword"
#define CPL_ERROR_MISSING_SEMICOLON "Missing semicolon (';')"


void throw_error(char* msg_type, char* msg_description, const char* file, int line, int col);
void throw_warning(char* msg_type, char* msg_description, const char* file, int line, int col);

#endif
