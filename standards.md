# Carbon Programming Language Standards
The purpose of this document is to basically outline the goal of the Carbon programming language and the introductory standards/features that help it achieve that end.

## Goal
The Carbon Programming Language's main goal is to be a relatively light-weight C-style language which avoids the bloat of C++ and idiomatic dogma of Java.  It should support basic OOP architecture like classes, encapsulation, inheritance, and polymorphism without being dogmatically tied to OOP.  It should include support for basic data structures like LinkedLists, ArrayLists, and HashTables.  These should be generic data structures whose contents are to be defined at compiletime.  The
language should also support generics/templates for custom objects/classes.  There should be native support for threading.  All basic C data types are to be included including explicit types that allocate memory predictably regardless of the underlying CPU architecture.  Each class will have a default destructor which can be overridden inside the class definition.  Unlike C/C++, there are no header files for managing dependencies -- classes themselves are scoped as public, protected, or
private and can be imported into other files depending on their scope.  A single file is not limited to a single like-named class.  Carbon Programming Language files (.cpl) compile directly to assembly.  Carbon Programming Language is a strongly-typed language and will support type aliases on imports to keep written code clean instead of building a dependence on an "auto" keyword like C++ which can add ambiguity.

## Basic Overview
This is a high-level summary of CLPs features.  Each feature is discussed in detail in the **Implementation** section.  CLP uses C-style comments: `//` for single line comments and `/* \n\n\n */` for multi-line comments.
### Data Types
There are 9 basic data types in CLP:

- **Booleans**:
    - `true`
    - `false`
- **Numerical**: All numerical types can be prefixed with `signed` or `unsigned`.
    - `byte`: This is an unsigned 8-bit whole number value.  Since CLP only targets x86, this is the smallest true data type
    - `short`: This is a signed 16-bit whole number value.
    - `int`: This is a signed 32-bit whole number value.
    - `long`: This is a signed 64-bit whole number value.
    - `float`: This is a signed 32-bit single-precision floating point value.
    - `double`: This is a signed 64-bit double-precision floating point value.
- **Strings and Characters**: Characters must be wrapped in single quotes ('c'), strings in double quotes ("string").
    - `char`: This is an 8-bit unsigned value representing an ASCII character.  Effectively an alias for `byte`.
    - `string`: Strings are simply an immutable array of characters with a null terminator.  Very basically, strings have values ("hello, world") and a length which is defined on initialization.
- **Others**:
    - `undefined`: Variables which are declared but not initialized are undefined (ex: `int value;`).
    - `void`: A type identifier which is used to indicate a function or method returns nothing.

### Expressions/Operators
- **Arithmetic**:
    - **Infix operators**: Infix operators are operators which lie between operands.  Operands can be variables, literals, or subexpressions.  Infix operators are whitespace insensitive.
        - `+`: Addition
        - `-`: Subtraction
        - `*`: Multiplication
        - `/`: Division
        - `%`: Modulus
        - `**`: Power
    - **Prefix operators**: Prefix operators are operators which lie directly in front of an operand.  Prefix operators cannot have whitespace.
        - `-`: Negate: Performs a twos-complement on a numerical operand regardless of signed-ness.
    - **Postfix operators**: Suffix operators are operators which lie directly behind an operand.  Suffix operators cannot have whitespace.
        - `++`: Increment by 1
        - `--`: Decrement by 1
- **Bitwise**:
    - **Infix operators**:
        - `<<`: Shift left
        - `>>`: Shift right
        - `&`: Bitwise and
        - `|`: Bitwise or
        - `^`: Bitwise xor
    - **Prefix operators**:
        - `~`: Bitwise not
- **Comparison and Equality**: All comparison and equality operators are infix operators and will attempt to implicitly cast for comparisons except for strict-equals (===)
    - `<`: Less than.
    - `>`: Greater than.
    - `<=`: Less than or equal to.
    - `>=`: Greater than or equal to.
    - `==`: Equal to.
    - `!=`: Not equal to.
    - `===`: strict-equal to: Type checks both operands without casting and then performs an equality check.
    - `!==`: type-strict not equal to: Returns `true` if operand types are different but values are the same.
    - `==!`: value-strict not equal to: Returns `true` if operand types are the same but values are different.
- **Logical**:
    - **Prefix operators**:
        - `!`: Boolean not: inverts operand.  Cannot have whitespace.
    - **Infix operators**: These operators short-circuit when possible.
        - `and`: Boolean and: returns `true` only if both operands are `true`.
        - `or`: Boolean or: returns `false` only if both operands are `false`.
        - `xor`: Boolean exclusive or (xor): returns `true` if only one operand is `true`.
- **String**:
    - `+`: Concatenate: returns a new string where the left string is at index 0 and the right string follows directly after the end of the left.  The left string's null terminator is removed.
    - `\`: Escape: a single backslash followed by one character escapes that character in the string.  Common examples are `\n`, `\t`, `\'`, `\"`, etc.  `'\0'` is a special case that only appears as a single character since the empty character can't appear in strings.
- **Assignment**: All assignment operators evaluate right operand and operate on the left operand
    - `=`: Left equals right
    - **Infix-assignment**: These are compound assignment operators where the left operand is assigned the value resulting from the corresponding arithmetic/bitwise infix operation between itself and the right operand
        - `+=`, `-=`, etc.; `<<=`, `>>=`, etc.

### Precedence
CLP's order of operations follows this heirarchy:

- Operations grouped in parentheses
- Functions
- Postfix operators (`++`, `--`)
- Prefix operators (`!`, `~`, `-`)
- Exponent (`**`)
- From left to right: multiplication, division, modulus
- From left to right: addition, subtraction
- Bitwise shift operators
- Comparison and equality operators
- Logical infix operators
- Assignment operators

### Statements
CLP uses semicolons to turn expressions into statements.  
CLP uses curly braces to group multiple statements together called code blocks.  Code blocks are locally scoped.  Code blocks from this point will be written as short-hand:  
`<code block>` is equivalent to `{ statement; statement; etc... }` where statements are typically written on separate lines.

### Variables
CLP declares and initializes variables much like C:
```
<modifiers> <datatype/object> <variable name>;
<variable name> [assignment operator] <expression>;
```
or
```
<modifiers> <datatype/object> <variable name> [assignment operator] <expression>;
```
Modifiers include statements like `const`, scoping statements like `public` or `private`, ownership like `static`, etc.
Data types can be any of the datatypes listed above or objects either from standard libraries or defined by the user.
The variable name follows basic C rules: it can only begin with an alphabetic character or an underscore and can only contain alphanumeric characters and underscores.  Variable names are case sensitive.  Variable names cannot be reserved keywords or defined objects.
CPL perfers lower camel case styling convention for typical variable names.  CPL prefers `static` variable names to be lower snake case and `const` variable names to be upper snake case.
CPL prefers private member variable names to have a leading underscore.

### Arrays
Arrays are immutable, flat memory structures whose size is calculated at compiletime.  The compiler keeps track of array sizes automatically and fetches them with the `len(arr)` function.  Arrays can be declared without being initialized like this:
```
<type>[<length>] <variable name>;
```
Arrays can also be declared and initialized in one line.  Element accesses are done like this:
```
<variable name>[<index>]
```
Arrays in CLP are 0-indexed.  If initializing an array whose elements are all the same value use this syntax:
```
<type>[<length>] <variable name> = <value>;
```
If initializing an array where each element is explicitly defined, use this syntax:
```
<type>[] <variable name> = { <element 1>, <element 2>, etc... };
```
The compiler will automatically calculate the length from the assignment.

### Control Flow
CLP has seven control flow structures:

- **Conditions**:
    - If: `if (<condition>) <statement; | code block>`  
    If the condition is true, the statement or code block is executed.  If the condition is false, the statement or code block are skipped.
    - Else-if: `else if (<condition>) <statement; | code block>`  
    Else-if must proceed an if statement.  It's condition will only be evaluated if the preceeding if statement's condition is false, otherwise it will be skipped.  If the else-if's condition is true, the statement or code block is executed, otherwise the statement or code block is skipped.
    - Else: `else <statement; | code block>`  
    Else must proceed an if or else-if statement.  It will execute the statement or code block only if the preceeding if/else-if statement's condition is false, otherwise it is skipped.
- **Loops**:
    - While: `while (<condition>) <statement; | code block>`  
    The while loop repeatedly executes a statement or code block until a condition is met.  When the condition is true, the statement or code block is skipped and the loop exits.
    - For: `for (<iterator variable definition>; <iterator variable break condition>; <iterator variable increment/decrement>)`  
    The for loop is a specialized while loop which tracks a numerical iterator, applying the specified increment/decrement until the break condition is met.  The iterator variable can be declared and/or initialized both outside or inside the for loop.  If defined inside the for loop, it is scoped to the for loop statement or code block.
- **Breaks**:
    - Break: `break;`  
    The break statement forcefully exits a loop.
    - Continue: `continue;`  
    The continue statement forcefully skips to the next iteration of a loop.

### Functions
Function calls use the following format:
```
<function name>(<optional comma-delimited arguments list>);
```
Function names are subject to the same rules as variable names.
A function referenced without parentheses or arguments list is treated like a function pointer variable.
Functions calls and function pointers are handled in the same way as method calls and method pointers except that method calls/pointers must be explicitly accessed from the method's class or instance.  More about methods in the **Classes** section.  Function calls are treated like values which means anywhere a value can be used, a function call can be substituted (first-class).

To define a function you must use the keyword `def`:
```
def <modifiers> <return type> <function name>(<optional comma-delimited parameters list>) <statement; | code block>`
```
A function that doesn't return anything should use `void` for its return type.  Modifiers include explicit scoping and ownership like `static` -- these are primarily used for methods.  Functions and methods are defined in the same way.  Functions can be defined inside other functions.  CLP supports function overloads and closures.

### Entry Point
Now is probably a good time to discuss the entry point for code in CLP.  CLP looks for a main function as its entry point.  The main function looks like this:
```
def int main(string[] args) {
    // code
}
```
The main method always returns an integer exit code, 0 for success.  The args array is an array of input parameters passed from stdin when launching the program.

### Classes
Classes in CLP are also first-class.  Classes are data structures which own and encapsulate data fields and functions.  Unlike Java, a single file can contain multiple classes.  Classes can also be wrapped in a scope called a module.  In large codebases, this is a useful means of packaging classes together to avoid ambiguity should there be classes with identical names.  Below is a template for defining a module:
```
module <module name> {
    // classes, functions, variables here
}
```
Below is a template for defining a class:
```
<scope> <static?> class <class name> {
}
```
Classes must be explicitly scoped as either public, protected, or private.  Public classes can be imported from anywhere.  Protected classes are only visible to all code in the scope of its file.  Private classes are only visible to all code in the scope of its definition.  
The static keyword is optional when defining a class.  A static class is a class which cannot be instantiated and thus all internal variables and methods are implicitly static since they cannot be accessed from an instance.  
The class name must abide by the same rules as variable names.  CLP prefers class names to use upper camel case.  All classes must use code blocks.

Class fields are treated like variables and must be explicitly declared inside the class.  Fields of non-static classes can be static.  Fields must be explicitly scoped.  Fields can be initialized at the point of declaration or in the constructor.  Initializing at the point of declaration results in fields that are already defined when the constructor is called.  Every class has a default empty constructor, `init()`, that can be overridden.  Defining the constructor works just
like normal functions except the constructor is always implicitly publicly scoped, the return type is always implicitly the class itself, and does not need the `def` keyword in front of it.

Class method definitions are treated like regular function definitions but inside a class scope.  There are two types of methods: instance methods and static methods.  Instance methods belong to a unique instance of a class and are thus accessed through that instance.  Static methods belong to the class itself and are shared across instances.  Instance fields cannot be referenced in a static method nor can instance methods be called in a static method.  The `this` keyword is a
reference to the most local class scope.  All references to instance methods or instance fields must be accessed by the instance itself, which, when inside the scope of a class, is done using the `this` keyword.  A class can reference its own static methods by calling them like normal functions.  Below is an example:
```
public class Foo {
    public int fooField;

    init() {
        this.fooField = 10;
    }

    def public static void exclaim() {
        println("I am a Foo!");
    }

    def public void exclaimWithContext() {
        exclaim();
        println("My value is " + this.fooField);
    }
}
```
Classes are instantiated using the following syntax: `<class name> <variable name> = new <class name>(<optional arguments>);` where the variable name is the instance reference.

### Interfaces
CLP also supports interfaces.  An interface is defined similar to a class except it is implementation agnostic and thus not instantiatable - it requires a class to implement it.  Interface fields and methods cannot be private.  Interface field declarations follow an identical template as class field declarations except they cannot be initialized.  Interface method declarations look like class method declarations except they end with a semicolon instead of a code block:
```
public interface bar {
    public int barField;
    public void barMethod();
}
```
Interfaces cannot be static nor have static members.

### Inheritance and Polymorphism
A common issue with inheritance heirarchies is the diamond problem in which class inheriting from two classes sharing the same base class cannot determine which of duplicate methods to call.  To get around this while still offering polymorphic flexibility, classes can only inherit from interfaces.  This is done with the `implements` keyword: `<scope> <static?> class <classname> implements <interface name>`.  Interfaces can also inherit from other interfaces, but the implementation details would
be forwarded on to the concrete subclass.  This approach avoids the diamond problem since any subclass by necessity must be the only concrete instance implementing inherited methods at the expense of being slightly more verbose.

### Generics
Generics allow classes or interfaces to operate on unknown types while still ensuring type safety.  A common use for this would be for data structures like LinkedLists.  In C, a user would have to write type-specific implementations of the same linked list structure to ensure type-safety (`void*` is not type safe!).  CLP takes the Java approach to this problem and allows users to use a generic as a placeholder at definition which is then made explicit when the class is instantiated.
CLP follows the same syntax as Java for this as well: `<?>` where `?` is one of the follow depending on its use case:

- `T`: This represents a generic type
- `E`: This represents a generic element
- `K`: This represents a generic key
- `V`: This represents a generic value

Java calls this "diamond notation" and this diamond notation directly follows the class name with no whitespace: `LinkedList<T>`.  When instantiating a generic class, CLP only requires the diamond notation on the object type: `LinkedList<ExplicitType> linkedList = new LinkedList()`.

### Standard Libarary
Many of these functions will be dependent on the operating system - POSIX/UNIX will have different implementations than DOS.  Ideally, these functions will yield the same end result, separating the user from being concerned with OS-specific implementation details.
Below is a list of standard library functions, classes, and constants divided by category:

**System**

- `exit(code)`
- `fork()`
- `exec(<shell command string>)`

**Memory manipulation** - actually shouldnt need this since we don't want the user getting nitty gritty with memory

- `memset()`
- `memcpy()`

**Arrays**

- `len(arr)`: compiler keeps track of array lengths in memory and returns them with this function.
- `sort(array)`: uses merge sort to sort an array of any type (more on how this works later).
- `reverse(array)`

**Strings**

- `string toStr(numeric a)`: in this case, toStr() is overloaded for each numeric type
- `string toHexStr(numeric a)`
- `string toBinStr(numeric a)`
- `string toOctalStr(numeric a)`
- `len(str)`: this is an override of the array len() function which takes a string as an argument.  It functions the same.
- `string[] split(str, delimiter)`
- `int contains(str, substr)`: returns index where substr begins, else -1
- `boolean startsWith(str, substr)`
- `boolean endsWith(str, substr)`
- `void toUpper(str)`: modified str in place
- `void toLower(str)`: modifies str in place
- `void trim(str)`: modifies str in place
- `void replace(str, old, new, n)`: replace old with new n times.  n=-1 for all

**Math**
All math functions can take any combination of numeric data types as parameters.

- `double min(a, b)`
- `double max(a, b)`
- `double exp(a)`
- `double log(a)`
- `double ln(a)`
- `double log(a, base)`
- `PI`: 0x1.921fb54442d18p+1 (3.141592653589793)
- `E`: 0x4005BF0A8B145769 (2.718281828459045)
- `double sin(radians)`
- `double sind(degrees)`
- `double cos(radians)`
- `double cosd(degrees)`
- `double tan(radians)`
- `double tand(degrees)`
- `double asin(radians)`: returns in radians
- `double asind(degrees)`: returns in degrees
- `double acos(radians)`
- `double acosd(degrees)`
- `double atan(radians)`
- `double atand(degrees)`
- `double sqrt(a)`: uses optimized sqrt function instead of just taking 1/2 power

**I/O**
For now, I/O is strictly limited to a tty

- `void println(string)`
- `void print(string)`: does not add newline at end

**Data Structures**

- `LinkedList<T>` class
- `ArrayList<T>` class
- `HashTable<K,V>` class
- `Stack<T>` class
- `Queue<T>` class
- `BinaryTree<T>` class
- `Heap<T>` class
- `Graph<T>` class

**Time**

- `now()`: current time in milliseconds from epoch time
- `startTimer()`: records current time using now() as a start time
- `stopTimer()`: records current time using now() as a stop time and resets both internal variables
- `elapsedTime()`: returns stop time - start time or -1 if error

**Threads**

coming soon to a language near you!

**Networking**

coming soon to a language near you!


## Implementation Details
Here I will go through each feature and provide a more detailed explanation for how it works, often using C to illustrate implementation details.

### Booleans
Booleans are effectively aliased unsigned bytes since they will be 1 byte long.  This is mainly done for memory consideration since general purpose cpu registers are addressible in, at the smallest, 1 byte segments (high and low registers) and memory for x86 machines is byte-aligned.  I will follow the C standard where a boolean with a value of 0 is false and anything else is considered true.  This is useful as it allows us to treat integers like booleans without a cast.  It also lets
us use the assembly instruction `test register, register` followed by `jz label` which sets the zero flag if the register is zero and then jumps if the zero flag is set.  This is much faster than trying an approach where true must be a specific value like 0xff (all bits asserted).

### Numerical Types
All numerical data types can be either signed or unsigned.  By default, the only unsigned numerical data type is the byte.  A byte is 8 bits long.  A signed byte is 8 bits long with the MSB being the sign bit.  
The short data type is signed by default and is 16 bits long.  It always represents an integer value.  
The int data type is signed by default and is 32 bits long.  This is the largest data type supported by all x86 CPUs, but since modern X86 CPUs have adopted the AMD64 architecture extension for decades now, I am going ignore this compatibility constraint.  
The long data type is signed by default and is 64 bits long.
The float data type is signed by default and is a single-precision 32 bit floating point value as defined by IEEE 754.  x86 CPUs calculate floats using the x87 FPU which makes implementation easy.
The double data type is signed by default and is a double-precision 64 bit floating point value as defined bye IEEE 754.  x86-64, again, has a solution for this which makes implementation fairly easy.

### Characters
The `char` type is unsigned by default and is an alias for the byte.  It's primary additional function is to aid code readability.  Setting a byte equal to a character literal has the same effect as setting a char equal to a character literal.

### Strings
Strings are `char` arrays and can be directly printed in the same way you would directly print an explicit `char`:
```
string str = "hello, ";
char[] carr = { "w", "o", "r", "l", "d", "!" };
print(str);
println(carr);
// prints "hello, world!" to the console
```
Like regular arrays, the compiler keeps track of string length and returns it when passing a string through the `len()` function.  CPL has a strings module in the standard library which contains functions that operate on strings like `substr()`, `split()`, `trim()`, etc.  Strings are heap-allocated and tracked by the garbage collector.  String mutations use realloc.
