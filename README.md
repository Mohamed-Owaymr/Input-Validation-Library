# Input Validation Library in C++

## Project Overview
This project is a **C++ Input Validation Library** designed to make user input handling safer, easier, and more reusable.  
When building any application that interacts with users, input validation is crucial to prevent invalid or unexpected data from causing runtime errors.
This library helps manage and validate inputs such as numbers, letters, yes/no responses, ranges, and strings efficiently.

---

## Features
- Read **positive, negative, or rational numbers** safely.
- Read **letters** and **yes/no responses** as boolean.
- Validate numbers **within a specific range**.
- Read **strings** with minimum and maximum length checks.
- **Enum handling** with `magic_enum` for option selection.
- Centralized **error handling** with clear user prompts.
- Reusable **template methods** for enum validation.

---

## Implementation Details
Each method in this library is designed to **handle input validation robustly**:

- **Number Validation:**  
  Methods like `readPositiveNumber`, `readNegativeNumber`, and `readRationalNumber` ensure the user input matches the required type. They use `cin.fail()` and custom checks (`isPositive`, `isNegative`, `isZero`) to validate inputs.

- **Letter and Boolean Validation:**  
  `readLetter` validates that the input is a single alphabetic character.  
  `readYesNoAsBool` converts user responses (`y/Y` or `n/N`) into a boolean value, using helper methods for clarity.

- **Range Validation:**  
  `readNumberInRange` ensures the input number falls within a specified range, supporting inclusive or exclusive bounds.

- **String Validation:**  
  `readString` reads a string while validating its length against given minimum and maximum constraints.

- **Enum Validation with `magic_enum`:**  
  Template methods like `readOptionNumber` and `isValidOptionNumber` allow the library to handle any enum type safely.  
  `magic_enum` is used to determine the **number of enum values dynamically**, ensuring option selection is always valid.

---

## Learning and Practicing OOP Concepts
This project was created as a **training ground for Object-Oriented Programming** in C++. Key concepts applied:

- **Encapsulation:**  
  Private helper methods like `cleanCin`, `printInvalidValueErrorMessage`, and `displayUserOptionsList` encapsulate internal logic, keeping the public API clean.

- **Static Methods:**  
  Since the library does not need object instances, all methods are static, allowing easy and direct use without creating objects.

- **Enums and Templates:**  
  Enums are combined with template methods to create **flexible and type-safe input options**, demonstrating polymorphism at the type level.

- **Error Handling:**  
  Input validation is centralized, demonstrating how methods can enforce constraints consistently.

---

## Why We Need This Library
- Prevents runtime errors caused by invalid user input.
- Reduces repetitive validation code in multiple projects.
- Provides a **clear, reusable interface** for different types of user inputs.
- Serves as a **learning project** for mastering OOP concepts, templates, enums, and structured error handling in C++.

---

## How to Use
```cpp
#include "Input.h"

int main() {
    float age = Input::readPositiveNumber("Enter your age");
    char gender = Input::readLetter("Enter M/F");
    bool agree = Input::readYesNoAsBool("Do you agree?");

    cout << "Age: " << age << ", Gender: " << gender << ", Agreed: " << agree << endl;
    return 0;
}
