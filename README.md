This project has been created as part of the 42 curriculum by alnassar.

# C++ - Module 06: C++ Casts

## Description
**C++ Module 06** is dedicated to mastering the four C++ type casting operators:
1. **`static_cast`**
2. **`reinterpret_cast`**
3. **`dynamic_cast`**
4. **`const_cast`**

In the C programming language, type casting is blunt and unchecked: `(type)expression`. C-style casting can inadvertently bypass `const`, misinterpret pointer types, and cause silent memory corruption.

C++ introduces four explicit, specialized casts to provide compile-time safety, runtime polymorphism verification, and explicit programmer intent.

---

## 📑 Summary of C++ Casts

| Cast Operator | Primary Use Case | Safety Check | Evaluation Exercise |
| :--- | :--- | :--- | :--- |
| **`static_cast`** | Well-defined conversions (numeric conversion, upcasting, void* to typed pointer). | **Compile-time**. Fails if types are incompatible. | **[ex00: ScalarConverter](ex00/)** |
| **`reinterpret_cast`** | Low-level bit reinterpretation (pointer to integer, pointer to unrelated pointer). | **Unsafe**. No bit conversion; simply reinterprets raw bits. | **[ex01: Serialization](ex01/)** |
| **`dynamic_cast`** | Safe downcasting in polymorphic class hierarchies (requires at least one `virtual` method). | **Runtime**. Uses RTTI / vtable. Returns `NULL` for pointers, throws exception for references. | **[ex02: Identify real type](ex02/)** |
| **`const_cast`** | Adding or removing `const` / `volatile` qualifiers. | **Compile-time**. Only modifies cv-qualifiers, not underlying type. | *Oral question during evaluation* |

---

## 🛠️ Exercises Overview

### [Exercise 00: Conversion of scalar types](ex00/)
- **Class**: `ScalarConverter` (pure static utility class with private constructors, non-instantiable).
- **Function**: `static void convert(const std::string& literal);`
- **Behavior**:
  - Detects the scalar literal (`char`, `int`, `float`, or `double`).
  - Supports pseudo-literals: `nan`, `nanf`, `+inf`, `+inff`, `-inf`, `-inff`.
  - Uses `static_cast` to convert to all 4 scalar types.
  - Formats output cleanly:
    - Displays `Non displayable` for unprintable ASCII chars (0–31, 127).
    - Displays `impossible` if out of bounds or semantically invalid.
    - Preserves trailing `.0f` / `.0` for whole numbers.

### [Exercise 01: Serialization](ex01/)
- **Class**: `Serializer` (pure static utility class with private constructors, non-instantiable).
- **Functions**:
  - `static uintptr_t serialize(Data* ptr);`
  - `static Data* deserialize(uintptr_t raw);`
- **Behavior**:
  - Uses `reinterpret_cast<uintptr_t>(ptr)` to convert a memory address into an integer.
  - Uses `reinterpret_cast<Data*>(raw)` to restore the integer back to a valid pointer.
  - Verifies that the restored pointer matches the original address and the data members remain fully usable.

### [Exercise 02: Identify real type](ex02/)
- **Classes**:
  - `Base`: Polymorphic base class with a `virtual ~Base()`.
  - `A`, `B`, `C`: Derived classes inheriting publicly from `Base`.
- **Functions**:
  - `Base* generate(void);`: Randomly instantiates `A`, `B`, or `C`.
  - `void identify(Base* p);`: Identifies the concrete type using `dynamic_cast<T*>(p)` and checks against `NULL`.
  - `void identify(Base& p);`: Identifies the concrete type using `dynamic_cast<T&>(p)` inside `try/catch` blocks (catches `std::exception`).
- **Crucial Rule**: The forbidden header `<typeinfo>` is **never** included.

---

## 📋 Evaluation Sheet Checklist

- [x] **Prerequisites**:
  - Compiles with `c++ -Wall -Wextra -Werror -std=c++98`.
  - No C++11 (or later) features.
  - No function implementations in header files.
  - No C memory functions (`malloc`, `free`, `printf`).
  - No `using namespace <ns_name>` or `friend` keyword.
  - Zero memory leaks (all allocated memory in `ex02` is properly `delete`d).
- [x] **Exercise 00**:
  - `ScalarConverter` has private constructors and static methods.
  - `static_cast` is used for conversions.
  - Handles pseudo-literals (`nan`, `inf`, etc.), quotes (`"'a'"`, `"'0'"`), unprintable chars, and overflows.
- [x] **Exercise 01**:
  - `Serializer` has private constructors and static methods.
  - `reinterpret_cast` used twice (`Data*` -> `uintptr_t` -> `Data*`).
  - Restored struct is verified usable.
- [x] **Exercise 02**:
  - `Base` has a virtual destructor.
  - `identify(Base* p)` checks for `NULL`.
  - `identify(Base& p)` uses `try/catch`.
  - `<typeinfo>` does not appear anywhere.

---

## 🚀 Compilation & Running

Each exercise contains its own independent `Makefile`:

```bash
# Exercise 00
cd ex00 && make
./convert 0
./convert 42.0f
./convert 42.42
./convert "'a'"
./convert nan

# Exercise 01
cd ../ex01 && make
./serialize

# Exercise 02
cd ../ex02 && make
./identify
```
