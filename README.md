# Carbon Programming Language
A study in designing and building a language and interpreter from scratch

## Top-level Details
View the [standards](standards.md) file to read about design choices for the language.

## Interpreter Architecture
The interpreter will doesn't compile directly to bytecode or to binary.  Rather, it translates the CLP code
to C code which then leverages the millions of lines of optimization done by the gcc compiler.  There may be
some functions that I hand-craft in assembly, but for the most part, the interpreter is really just a translator.

## Contributing
I am not accepting contributions.
