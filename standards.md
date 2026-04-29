# Carbon Programming Language Standards
The purpose of this document is to basically outline the goal of the Carbon programming language and the introductory standards/features that help it achieve that end.

## Goal
The Carbon Programming Language's main goal is to be a relatively light-weight C-style language which avoids the bloat of C++ and idiomatic dogma of Java.  It should support basic OOP architecture like classes, encapsulation, inheritance, and polymorphism without being dogmatically tied to OOP.  It should include support for basic data structures like LinkedLists, ArrayLists, and HashTables.  These should be generic data structures whose element type is defined on instantiation.  The
language also supports generics for custom objects/classes.  CLP will support threading.  All basic C data types are to be included including explicit types that allocate memory predictably regardless of the underlying CPU architecture.  Each class will have a default destructor which can be overridden inside the class definition.  Unlike C/C++, there are no header files for managing dependencies.  Classes themselves are scoped as public, protected, or
private and can be imported into other files depending on their scope.  A single file is not limited to a single like-named class.  Carbon Programming Language files (.cpl) compile directly to assembly.  Carbon Programming Language is a strongly-typed language and will support type aliases on imports to keep written code clean instead of building a dependence on an "auto" keyword like C++ which can add ambiguity.
The standard library functions should be designed as adapters for operating system specific implementations.  This abstraction will allow CLP to be cross platform by compiling separate binaries for different operating systems from the same code.

## Basic Overview
This is a high-level summary of CLPs features.  CLP uses C-style comments: `//` for single line comments and `/* \n\n\n */` for multi-line comments.
### Data Types
There are 9 basic data types in CLP:

- **Booleans**:
    - `bool`: Booleans can be either `true` or `false`.  Booleans are unsigned bytes where 0 is `false` and >0 is `true`.
- **Numerical**: 
    - `ubyte`: This is an unsigned 8-bit integer value. `ubyte` and `sbyte` are the smallest data types in CLP.
    - `sbyte`: this is a signed 8-bit integer value.
    - `byte`: This is an alias for `ubyte`.  This is the only non-prefixed data type to be unsigned by default, hence it's alias.
    - `int16`: This is a signed 16-bit integer value.
    - `uint16`: This is an unsigned 16-bit integer value.
    - `int32`: This is an signed 32-bit integer value.
    - `uint32`: This is an unsigned 32-bit integer value.
    - `int64`: This is a signed 64-bit integer value.
    - `uint64`: This is an unsigned 64-bit integer value.
    - `float32`: This is a 32-bit single-precision floating point value (IEEE 754).
    - `float64`: This is a 64-bit double-precision floating point value (IEEE 754).
- **Strings and Characters**: Characters must be wrapped in single quotes: `'c'`; strings in double quotes: `"string"`.
    - `char`: This is an alias for `ubyte` representing ASCII characters.
    - `string`: Strings are simply an immutable array of `char`s with a null terminator.  Very basically, strings have values ("hello, world") and a length which is defined on initialization.
- **Others**:
    - `null`: Variables or objects that reference unallocated or uninitialized memory are `null`.
    - `void`: A type identifier which is used to indicate "no type".

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
        - `-`: Negate: effectively multiplies a signed number (integer or float) by -1.  Will result in a compiletime error for unsigned integers.
    - **Postfix operators**: Suffix operators are operators which lie directly behind an operand.
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
- **Comparison and Equality**: All comparison and equality operators are infix operators.  All operators will throw a compiletime error if types are not equal.
    - `<`: Less than.
    - `>`: Greater than.
    - `<=`: Less than or equal to.
    - `>=`: Greater than or equal to.
    - `==`: Equal to.
    - `!=`: Not equal to. 
- **Logical**:
    - **Prefix operators**:
        - `!`: Boolean not: inverts operand. 
    - **Infix operators**: These operators short-circuit when possible.
        - `and`: Boolean and: returns `true` only if both operands are `true`.
        - `or`: Boolean or: returns `false` only if both operands are `false`.
        - `xor`: Boolean exclusive or (xor): returns `true` if only one operand is `true`.
- **String**:
    - `+`: Concatenate: returns a new string where the left string is at index 0 and the right string follows directly after the end of the left.  The left string's null terminator is removed.
    - `\`: Escape: a single backslash followed by one character escapes that character in the string.  Common examples are `\n`, `\t`, `\'`, `\"`, etc.  `'\0'` is a special case that only appears as a single character since the empty character can't appear in strings.
- **Assignment**: All assignment operators evaluate right operand and operate on the left operand
    - `=`: Left equals right
    - **Compound assignment**: These are operators where the left operand is assigned the value resulting from the corresponding arithmetic/bitwise infix operation between itself and the right operand
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
CLP is a statement-oriented language and uses semicolons to turn expressions into statements.  
CLP uses curly braces to group multiple statements together called code blocks for control flow.  Code blocks are locally scoped.

### Variables
CLP declares and initializes variables much like C: declaration and initialization in one line, or in two lines (split declaration).  CLP handles a split declaration like two assignments where it first assigns a variable to `null` and then re-assigns to a value.  For this reason, immutable or `const` variables cannot use split declarations (excepting strings).
```
<modifiers?> <type> <variable name>;
<variable name> = <expression>;
// or
<modifiers?> <type> <variable name> = <expression>;
```
Example:
```
int32 var1;
var1 = 10;
// or
float32 var2 = 123;

// not allowed
const float32 pi;
pi = 3.1415;
```
Modifiers include statements like `const`, scoping statements like `public` or `private`, ownership like `static`, etc.
Types can be any of the data types listed above or objects either from standard libraries or defined by the user.
The variable name follows basic C rules: it can only begin with an alphabetic character or an underscore and can only contain alphanumeric characters and underscores.  Variable names are case sensitive.  Variable names cannot be reserved keywords or defined objects.
CPL perfers lower camel case styling convention for typical variable names.  CPL prefers `static` variable names to be lower snake case and `const` variable names to be upper snake case.
CPL prefers private member variable names to have a leading underscore.
Variables can be cast by prepending a variable name with `(<type>)`.  CLP allows implicit type conversion via casting (`int16` &harr; `int32`, `float32` &harr; `float64`, `floatXX` &harr; `intXX`).  Converting from a larger type truncates the top bits of the larger type.  Converting from a float to an int truncates the decimal.
```
int32 oldInt = 69420;
float32 oldFloat = 69.420;

// Direct cast
int64 direct = (int64)oldVar;

// Truncates top 48 bits
int16 lossy = (int16)oldVar;

// Implicitly converts float to int
int32 conversion = (int32)oldFloat;

// Implicit lossless conversion and then truncates top 16 bits
int16 lossyConversion = (int16)oldFloat;
```
Object casting is discussed in the [Inheritance and Polymorphism](#Inheritance-and-Polymorphism) section.

### Arrays
Arrays are fixed-length, flat memory structures.  The compiler keeps track of array sizes and automatically and fetches them with the `len(arr)` function.  Arrays can be declared without being initialized much like variables:
```
<modifiers?> <type>[<length>] <variable name>;
```
Arrays can also be declared and initialized in one line.  If initializing an array whose elements are all the same value use this syntax:
```
<modifiers?> <type>[<length>] <variable name> = <value>;
```
If initializing an array where each element is explicitly defined, use this syntax:
```
<modifiers?> <type>[] <variable name> = { <element 1>, <element 2>, etc... };
```
The compiler will automatically calculate the length from the assignment.  
Arrays in CLP are 0-indexed.  Element accesses are done like this:
```
<variable name>[<index>]
```
Example:
```
// Split declaration that sets all elements to 420.67
float64[69] funnyArray;
funnyArray = 420.67;

string[2] helloWorld = { "Hello", "world" };

println(funnyArray[42]); // prints 420.67
println(helloWorld[0]);  // prints "Hello"
```
The `const` modifier prevents array elements from being changed.

### Control Flow
"Conditions" are evaluated boolean expressions.
CLP has seven control flow structures:

- **Conditions**:
    - `if`: `if (<condition>) <statement; | code block>`  
    If the condition is true, the statement or code block is executed.  If the condition is false, the statement or code block are skipped.
    - `else if`: `else if (<condition>) <statement; | code block>`  
    Else-if must proceed an if statement.  It's condition will only be evaluated if the preceeding if statement's condition is false, otherwise it will be skipped.  If the else-if's condition is true, the statement or code block is executed, otherwise the statement or code block is skipped.
    - `else`: `else <statement; | code block>`  
    Else must proceed an if or else-if statement.  It will execute the statement or code block only if the preceeding if/else-if statement's condition is false, otherwise it is skipped.
- **Loops**:
    - `while`: `while (<condition>) <statement; | code block>`  
    The while loop repeatedly executes a statement or code block until a condition is met.  When the condition is true, the statement or code block is skipped and the loop exits.
    - `for`: `for (<index variable definition>; <index variable break condition>; <index variable increment/decrement expression>)`  
    The for loop is a specialized while loop which tracks an integer index, applying the specified increment/decrement expression until the break condition is met.  The index variable can be declared and/or initialized both outside or inside the for loop definition.  If defined inside the for loop definition, it is scoped to the for loop statement or code block.
    - `foreach`: Will probably add this later because its nice.
- **Breaks**:
    - `break`: `break;`  
    The break statement forcefully exits a loop.
    - `continue`: `continue;`  
    The continue statement forcefully skips to the next iteration of a loop.

Examples:
```
if (condition0) doSomething();
else if (condition1) {
    // do stuff
} else {
    // do stuff
}

while(condition3) {
    // do stuff
    if (condition4) {
        // do stuff
        break;
    }
    // do stuff
}
// break exits the loop

for (int32 i = 0; i < 100; i++) {
    // do stuff
    if (condition5) {
        // do stuff;
        continue;
    }
    // more stuff - skipped if continue is called
}
```

### Functions
Function calls use the following format:
```
<function name>(<arguments list?>);
```
Function names are subject to the same rules as variable names.
A function referenced without parentheses or arguments list is treated like a function pointer variable and can be passed like a variable.
Functions calls and function pointers are handled in the same way as method calls and method pointers except that method calls/pointers must be explicitly accessed from the method's class or instance.  More about methods in the [Classes](#Classes) section.  Function calls are treated like values which means anywhere a value can be used, a function call can be substituted (first-class).

To define a function, you must specify any optional modifiers, the return type, function name, optional parameters list enclosed between parentheses, and then a code block.
```
<modifiers?> <type> <function name>(<parameters list?>) <code block>`
```
A function definition does not have to occur above its function call.  A function that doesn't return anything should use `void` for its return type.  Void functions do not need a return statement.  Modifiers include explicit scoping and ownership like `static` -- these are primarily used for methods.  Functions and methods are defined in the same way.  Classes cannot contain functions.  CLP supports function overloads and closures.

Example:
```
int64 addNumbers(int64 a, int64 a) {
    if (a + b < a or a + b < b) {
        logError("sum is too large.");
        exit(1);
    }
    return a + b;
}

void logError(string message) {
    println("Error: " + message);
}

```

### Entry Point
Now is probably a good time to discuss the entry point for code in CLP.  CLP looks for a main function as its entry point.  The main function looks like this:
```
int main(string[] args) {
    // code

    return 0;
}
```
The main method always returns an integer exit code - 0 for success.  The args array is an array of input parameters passed from stdin when launching the program.  `args[0]` is the execution string used to launch the program (`./launch`).

### Classes
Classes in CLP are also first-class.  Classes are data structures which own and encapsulate data fields and functions (called methods).  Unlike Java, a single file can contain multiple classes.  Classes can also be wrapped in a scope called a module.  In large codebases, this is a useful means of packaging classes together to avoid ambiguity should there be classes with identical names.  Modules are very similar to C++ namespaces.  Below is a template for defining a module:
```
module <module name> {
    // classes, functions, variables here
}
```
Below is a template for defining a class:
```
<scope> <static?> class <class name> <code block>
```
Classes must be explicitly scoped as either public, protected, or private.  Public classes can be imported from anywhere.  Protected classes are only visible to all code in the scope of its file.  Private classes are only visible to all code in the scope of its definition.  
The static keyword is optional when defining a class.  A static class is a class which cannot be instantiated and thus all internal variables and methods are implicitly static since they cannot be accessed from an instance.  
The class name must abide by the same rules as variable names.  CLP prefers class names to use upper camel case.  All classes must use code blocks.

Class fields are treated like variables and must be explicitly declared inside the class.  Fields of non-static classes can be static.  Fields must be explicitly scoped.  Fields can be initialized at the point of declaration or in the constructor.  Initializing at the point of declaration results in fields that are already defined when the constructor is called.  Every class requires the user to implement a constructor called `init()`.  Defining the constructor works just
like normal functions except the constructor is always implicitly publicly scoped, the return type is always implicitly the class itself and the constructor always implicitly returns `this`.  Explicitly returning `this` or specifying the class as the return type will result in a compiletime error.
Class method definitions are treated like regular function definitions but inside a class scope.  There are two types of methods: instance methods and static methods.  Instance methods belong to a unique instance of a class and are thus accessed through that instance.  Static methods belong to the class itself and are shared across instances.  Instance fields cannot be referenced in a static method nor can instance methods be called in a static method.  The `this` keyword is a
reference to the most local class scope.  All references to instance methods or instance fields must be accessed by the instance itself, which, when inside the scope of a class, is done using the `this` keyword.  A class can reference its own static methods by calling them like normal functions.  Below is an example:
```
public class Foo {
    public int32 fooField;

    init(int32 fooField) {
        this.fooField = fooField;
    }

    public static void exclaim() {
        println("I am a Foo!");
    }

    public void exclaimWithContext() {
        exclaim();
        println("My value is " + this.fooField);
    }
}
```
Classes are instantiated using the following syntax:
```
<scope?> <class name> <variable name> = new <class name>(<arguments list?>);
```
Example:
```
Foo myFoo = new Foo(10);
```
Scope only applies to class compositions where class instantiations are treated like member fields.  Otherwise, class instantiations are scoped as locally as possible.

### Interfaces
CLP also supports interfaces.  An interface is defined similar to a class except it is implementation-agnostic and thus not instantiatable: interfaces are simply contracts specifying required methods that contracted classes must implement.  Interfaces cannot contain fields.  Interface method declarations cannot be private.  Interface method declarations look like regular method definitions, but are terminated with a semicolon instead of a code block.
```
public interface Fooable {
    public void fooMethod();
}
```
Interfaces cannot be static nor have static members.  CLP prefers interface names to be upper camel case and end in "able".

### Inheritance and Polymorphism
A common issue with inheritance heirarchies is the diamond problem in which a class inheriting from two classes sharing the same base class cannot determine which of duplicate methods to call.  To get around this while still offering polymorphic flexibility, classes cannot inherit from other classes.  Instead, they can only implement interfaces.  This is done with the `implements` keyword in a class definition: `<scope> <static?> class <class name> implements <interface name>`.  Interfaces can also implement other interfaces, but the implementation details would
be forwarded on to the concrete subclass.  An interface which implements another interface does not have to explicitly declare it's contracted methods.  For example:
```
public interface Fooable {
    public void fooMethod();
}

public interface Barable implements Fooable {
    public void barMethod();

    /* This is implicit
    public void fooMethod();
    */
}

public class Concrete implements Barable {
    //...
    // Contracted method implementations
    public void barMethod() { //... }
    public void fooMethod() { //... }
}
```
This approach avoids the diamond problem since any subclass, by necessity, must be a leaf in it's interface contract tree at the expense of being slightly more verbose.  These design choices intentionally encourages code to use class composition instead of inheritance to achieve polymorphic behavior.

A class cannot be cast to another class.  A class implementing an interface can type-referenced as its interface, but its interface reference cannot access subclass fields or methods because the interface reference has no knowledge of its subclass instance.
```
public interface Fooable {
    public void fooMethod();
}

public class ClassA implements Fooable {
    // ...
    public void classAMethod() { //... }
}

public class ClassB implements Fooable {
    // ...
    public void classBMethod() { //... }
}

// somewhere else...
public void doFoo(Fooable fooable) {
    fooable.fooMethod(); // will pass at compiletime because fooMethod() is in Fooable
    fooable.classBMethod(); // will fail at compiletime since classBMethod() is not in Fooable
    
    // to access a subclass method, we need convert fooable to its subclass.
    // we can check if a subclass implements an interface using `is`
    if (fooable is ClassB) {
        ClassB classB = fooable;
        classB.classBMethod(); // no runtime error because we checked fooable's subclass type

        ClassA classA = fooable; // runtime error since assignment operators are type safe.
    }
}
```
When a subclass gets passed as its interface (`ClassB` passed as a `Fooable` argument), no data is lost at runtime, but the compiler is not guaranteed to know at compiletime which subclass is being passed.  As such, `fooable` is the full reference to its subclass, but to maintain type safety, the compiler requires a new subclass variable to be assigned to `fooable` to gain access to the subclasses data.

### Generics
Generics allow classes or interfaces to operate on unknown types while still ensuring type safety.  A common use for this would be for data structures like LinkedLists.  In C, a user would have to write type-specific implementations of the same linked list structure to ensure type-safety (`void*` is not type safe!).  CLP takes the Java approach to this problem and allows users to use a generic as a placeholder at definition which is then made explicit when the class is instantiated.
CLP follows the same syntax as Java for this as well: `<?>` where `?` is one of the follow depending on its use case:

- `T`: This represents a generic type
- `E`: This represents a generic element
- `K`: This represents a generic key
- `V`: This represents a generic value

Java calls this "diamond notation" and this diamond notation directly follows the class name with no whitespace: `LinkedList<T>`.  When instantiating a generic class, CLP only requires the diamond notation on the object type: `LinkedList<ExplicitType> linkedList = new LinkedList()`.

### Enums
Enums use generics and can be initialized in two ways:
```
Enum <enum name> = {
    <FIELD>,
    <FIELD>,
    ...
};
```
and second:
```
Enum<type> <enum name> = {
    <FIELD> = <value/object of type>,
    ...
};
```
For example:
```
Enum Direction = {
    NORTH, // `stringify(Direction.NORTH);` is "NORTH"
    SOUTH, // `println(Direction.SOUTH);` prints "1"
    EAST,
    WEST
};
// or 
Enum<char> Direction = {
    NORTH = 'n', // stringify works the same as above
    SOUTH = 's', // `println(Direction.SOUTH)` prints "s"
    EAST = 'e,
    WEST = 'w'
};
```
Since the code block for enums aren't used as control flow but instead as part of a statement, the closing curly brace must be terminated with a semicolon.
It is recommended that enum fields are upper snake case.  Enum fields are accessed through the enum identifier: `<enum name>.<FIELD>`.  Enums in CLP are also
loosely disguised hashtables where, during definition, fields can be assigned to values (second way).  If defined this way, the type must be passed using 
diamond notation.  Therefore, all values must be the same type.  If no values are assigned, the diamond can be omitted.  Enum values are automatically 
assigned to their integer position in the structure, and if a user wants to get the field name as a string, they can use the `stringify()` function from the 
standard library.  Enums are immutable.

### Standard Libarary
Many of these functions will be dependent on the operating system - POSIX/UNIX will have different implementations than DOS.  Ideally, these functions will yield the same end result, separating the user from being concerned with OS-specific implementation details.
Below is a list of standard library functions, classes, and constants divided by category:

**System**

- `exit(<code integer>)`
- `uint32 fork()`: return's child pid. -1 for error.
- `uint32 exec(<shell command string>)`: returns exit code on program exit, -1 for error.

**Memory manipulation** - actually shouldnt need this since we don't want the user getting nitty gritty with memory

- `memset()`
- `memcpy()`

**Arrays**

- `len(arr)`: compiler keeps track of array lengths in memory and returns them with this function.
- `sort(array)`: uses merge sort to sort an array of any type (more on how this works later).
- `reverse(array)`

**Enums**
- `Enum<T>`: enum structure
- `stringify(enum.field)`: convert enum field to string

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

