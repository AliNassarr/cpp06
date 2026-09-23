# 📚 CPP Module 06: Complete Study Guide & Peer Evaluation Defense

This study guide is designed to help you thoroughly understand every line of code in **C++ Module 06**, ace your 42 peer evaluation, and confidently explain all concepts to your evaluators.

---

## 📑 Table of Contents
1. [The Big Picture: Why C++ Casts?](#1-the-big-picture-why-c-casts)
2. [The 4 C++ Casting Operators](#2-the-4-c-casting-operators)
3. [Exercise 00: ScalarConverter (`static_cast`)](#3-exercise-00-scalarconverter-static_cast)
4. [Exercise 01: Serialization (`reinterpret_cast`)](#4-exercise-01-serialization-reinterpret_cast)
5. [Exercise 02: Identify Real Type (`dynamic_cast`)](#5-exercise-02-identify-real-type-dynamic_cast)
6. [Top Peer Evaluation Questions & Answers](#6-top-peer-evaluation-questions--answers)

---

## 1. The Big Picture: Why C++ Casts?

In C, whenever you needed to convert a type, you wrote:
```c
int a = 42;
double b = (double)a;      // Numeric conversion
int* ptr = (int*)malloc(10); // Void pointer conversion
char* p = (char*)a;         // Dangerous pointer conversion!
```

### What was wrong with C-style casts?
1. **Too blunt & unchecked**: A C-style cast can do almost anything—convert numbers, cast away `const`, convert incompatible pointers, reinterpret bits. The compiler won't warn you if you make a catastrophic mistake.
2. **Hard to search in code**: Searching for `(int)` in a codebase of 50,000 lines gives hundreds of false positives. Searching for `static_cast<int>` or `reinterpret_cast` takes 1 second (`grep reinterpret_cast`).
3. **Doesn't communicate intent**: When another programmer reads `(char*)p`, they don't know if you intended to strip `const`, reinterpret raw memory, or perform an inheritance cast.

C++ solves this by splitting casting into **four explicit, specialized operators**:
- `static_cast`
- `reinterpret_cast`
- `dynamic_cast`
- `const_cast`

---

## 2. The 4 C++ Casting Operators

### 1. `static_cast<NewType>(expression)`
- **When to use**: Well-defined, predictable conversions known at compile time.
- **Examples**:
  - Converting numeric types (`int` to `double`, `float` to `int`).
  - Explicit enum-to-integer conversions.
  - Safe upcasting in class hierarchies (derived pointer to base pointer).
  - Converting `void*` to a typed pointer.
- **Safety**: Checked at compile time. Incompatible conversions (e.g. `int*` to `float*`) will trigger a compiler error.

### 2. `reinterpret_cast<NewType>(expression)`
- **When to use**: Low-level reinterpretation of bits without changing the bit pattern.
- **Examples**:
  - Converting a pointer to an integer (`Data*` to `uintptr_t`).
  - Converting an integer back to a pointer (`uintptr_t` to `Data*`).
  - Converting unrelated pointer types (`char*` to `int*`).
- **Safety**: Unchecked and potentially dangerous. The compiler assumes you know exactly what you are doing with hardware or memory alignment.

### 3. `dynamic_cast<NewType>(expression)`
- **When to use**: Safe downcasting in polymorphic class hierarchies (casting a `Base*` or `Base&` down to `Derived*` or `Derived&`).
- **Requirement**: The base class **must have at least one virtual function** (typically `virtual ~Base()`). This creates a Virtual Method Table (vtable) and enables Runtime Type Information (RTTI).
- **Behavior**:
  - **Pointers**: If the cast succeeds, returns the valid derived pointer. If it fails (the object is not of that type), it returns `NULL`.
  - **References**: References cannot be `NULL` in C++. Therefore, if the cast fails, it throws a `std::bad_cast` exception!

### 4. `const_cast<NewType>(expression)`
- **When to use**: Adding or removing `const` or `volatile` qualifiers from a variable.
- **Rule**: It can *only* change cv-qualifiers, not the underlying type.
- **Warning**: Modifying an object that was originally declared `const` after casting away its `const` causes **Undefined Behavior**.

---

## 3. Exercise 00: ScalarConverter (`static_cast`)

### Objective
Given a string literal representing a scalar value (`char`, `int`, `float`, or `double`), detect its type and print its converted representation in all 4 types using `static_cast`.

### Architecture: The Pure Static Class
```cpp
class ScalarConverter
{
public:
    static void convert(const std::string& literal);

private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter& other);
    ScalarConverter& operator=(const ScalarConverter& rhs);
    ~ScalarConverter();
};
```
- **Why are constructors private?**
  `ScalarConverter` is a utility tool (like `Math` in other languages). You should never instantiate it with `new ScalarConverter()` or `ScalarConverter sc;`. Making all constructors and the destructor `private` guarantees it cannot be instantiated.

### The Conversion Logic Flow
1. **Empty check**: If `literal.empty()`, print `impossible` for all types.
2. **Pseudo-literals**:
   - `nan` / `nanf` $\rightarrow$ `char: impossible`, `int: impossible`, `float: nanf`, `double: nan`.
   - `+inf` / `+inff` / `inf` / `inff` $\rightarrow$ `float: +inff`, `double: +inf`.
   - `-inf` / `-inff` $\rightarrow$ `float: -inff`, `double: -inf`.
3. **Char Literals**:
   - Quoted: `'a'`, `'0'`, `'*'` (length is 3, begins and ends with `'`).
   - Unquoted non-digit: `a`, `z`, `*` (length is 1, not a digit).
4. **Numeric Parsing**:
   - Use `std::strtod` to parse numbers.
   - Allow optional trailing `'f'` for float literals (`42.0f`).
   - If invalid characters exist, mark as `impossible`.
5. **Output Formatting**:
   - `char`: Check if `0 <= val <= 127`. If so, use `std::isprint(static_cast<int>(val))` to decide between displayable (`'c'`) or `Non displayable`. If out of range, print `impossible`.
   - `int`: Check against `std::numeric_limits<int>::min()` and `max()`. If within bounds, print `static_cast<int>(val)`.
   - `float` & `double`: Check if whole number (`std::floor(val) == val`). If whole number, format with `.0f` / `.0`. If it has decimal places, preserve them.

---

## 4. Exercise 01: Serialization (`reinterpret_cast`)

### Objective
Serialize a pointer to an object into an unsigned integer type (`uintptr_t`), and deserialize that integer back into a pointer to the original object.

### The Data Struct
```cpp
struct Data
{
    int         id;
    std::string name;
    double      value;
};
```

### The Serialization Methods
```cpp
uintptr_t Serializer::serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data*>(raw);
}
```

### Why `uintptr_t`?
- In 32-bit systems, pointers are 32 bits (4 bytes).
- In 64-bit systems, pointers are 64 bits (8 bytes).
- A standard `int` is typically 32 bits on both! If you cast a 64-bit pointer to an `int`, you truncate half of the memory address and corrupt it.
- **`uintptr_t`** (defined in `<stdint.h>`) is an unsigned integer guaranteed by the C/C++ standard to be wide enough to hold a pointer address on any architecture without data loss.

---

## 5. Exercise 02: Identify Real Type (`dynamic_cast`)

### Objective
Create a base class `Base` and three empty derived classes `A`, `B`, `C`. Given an unknown pointer or reference to `Base`, determine which concrete class it actually is at runtime.

### Why does `Base` need `virtual ~Base()`?
`dynamic_cast` relies on **RTTI (Run-Time Type Information)**. For RTTI to exist, the class **must be polymorphic**, meaning it must have at least one virtual method. A virtual destructor:
1. Makes `Base` polymorphic so `dynamic_cast` can read the class's vtable.
2. Ensures safe deletion through base pointers (`delete instance`).

### 1. Identifying via Pointer: `void identify(Base* p)`
```cpp
void identify(Base* p)
{
    if (p == NULL)
        return;

    if (dynamic_cast<A*>(p) != NULL)
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p) != NULL)
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p) != NULL)
        std::cout << "C" << std::endl;
}
```
- When casting a pointer, `dynamic_cast<Derived*>(p)` returns `NULL` if `p` is not pointing to an instance of `Derived`.

### 2. Identifying via Reference: `void identify(Base& p)`
```cpp
void identify(Base& p)
{
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (const std::exception&) {}

    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (const std::exception&) {}

    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (const std::exception&) {}
}
```
- In C++, **references can never be NULL**.
- Therefore, when `dynamic_cast<Derived&>(p)` fails, it cannot return `NULL`. Instead, it **throws an exception** (`std::bad_cast`).
- **Why catch `std::exception` instead of `std::bad_cast`?**
  The subject states: `"(In case you're wondering, the header <typeinfo> must not appear anywhere.)"`
  `std::bad_cast` is defined in `<typeinfo>`. However, `std::bad_cast` inherits publicly from `std::exception` (from `<exception>`). Catching `const std::exception&` catches the `bad_cast` perfectly without violating the forbidden header rule!

---

## 6. Top Peer Evaluation Questions & Answers

### Q1: What are the 4 C++ cast operators and what are their differences?
> **Answer**:
> 1. `static_cast`: For well-defined, compile-time conversions (numeric casts, safe upcasts, `void*` casts).
> 2. `reinterpret_cast`: For raw, low-level bit reinterpretation (pointer-to-integer, pointer-to-pointer).
> 3. `dynamic_cast`: For runtime-checked downcasting across polymorphic class hierarchies using RTTI and vtables.
> 4. `const_cast`: For adding or removing `const` or `volatile` qualifiers.

### Q2: Why is `ScalarConverter` (ex00) non-instantiable?
> **Answer**:
> Because it is a static utility class designed only to hold pure functions. It has no internal state or non-static member variables. By making its default constructor, copy constructor, assignment operator, and destructor `private`, we enforce at compile time that no one can instantiate or clone it.

### Q3: Why did you use `uintptr_t` instead of `unsigned long` or `int` in ex01?
> **Answer**:
> On different architectures (e.g., 32-bit vs 64-bit), the sizes of `int` and `long` vary across operating systems. `uintptr_t` from `<stdint.h>` is specifically designed and guaranteed by the standard to match the pointer width of the target machine, ensuring no bits of the pointer address are lost during conversion.

### Q4: In ex02, why can't `identify(Base& p)` just check for `NULL`?
> **Answer**:
> In C++, references are aliases to existing objects and syntactically cannot be `NULL`. When a pointer `dynamic_cast` fails, it returns `NULL`. But for a reference `dynamic_cast`, since it cannot return `NULL`, C++ is designed to throw a `std::bad_cast` exception.

### Q5: In ex02, why did you catch `std::exception` instead of `std::bad_cast`?
> **Answer**:
> The subject explicitly forbids including `<typeinfo>`, which is where `std::bad_cast` is declared. However, `std::bad_cast` inherits publicly from `std::exception` in `<exception>`, which is allowed. Catching `const std::exception&` safely catches `std::bad_cast` without including `<typeinfo>`.

### Q6: What happens if `Base` doesn't have a virtual destructor in ex02?
> **Answer**:
> `dynamic_cast` requires the target class hierarchy to be polymorphic. If `Base` has no virtual functions, it has no virtual method table (vtable) and no RTTI. The compiler will reject the code with `error: cannot dynamic_cast 'p' (of type 'class Base*') to type 'class A*' (source type is not polymorphic)`.
