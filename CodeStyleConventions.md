Naming
------

0. Use _const_ as much as possible.
   Inputs should always be const. No parameter should be input and output.

1. Variable names are mixed case starting with lower case.

  ```cpp
  float x;
  int numberOfPairs;
  ```

2. Names representing types are mixed case starting with upper case.

  ```cpp
  Point p;
  HashTable hashTable;
  ```

3. Names representing functions and methods must be verbs and are written in
   mixed case starting with lower case.

  ```cpp
  void function();
  Point getIntersection(Line line1, Line line2);
  ```

4. Named constants (including enumeration values) are all uppercase using
   underscore to separate words.

  ```cpp
  const int MAX_ITERATIONS = 100;
  enum Color {
    WHITE,
    BLACK,
    RED
  };
  ```

5. Names representing namespaces are all lowercase and is recommended to be
   very small (5 or less letters).

  ```cpp
  core::Profiler profiler;
  ```

6. Private class variables end with underscore.

  ```cpp
  class SomeClass {
  private:
    int length_;
  };
  ```

7. The name of the object is implicit, and should be avoided in a method name

  ```cpp
  line.getLength(); // NOT: line.GetLineLength();
  ```

8. Booleans start with _is_.

  ```cpp
  bool isKicking;
  ```

9. Collections use the plural form.

  ```cpp
  vector<Point> points;
  int values[];
  ```

10. Abbreviations in names should be avoided.

  ```cpp
  computeAverage(); // NOT: CompAvg();
  ```

Files
-----

11. Header files must contain an __include guard__.

    __Include guards__ should be ```<project_name>_<file path>_<file name>_H```.

  ```cpp
  #ifndef ROBOIME_CORE_PROFILER_H
  #define ROBOIME_CORE_PROFILER_H
    ...
  #endif // ROBOIME_CORE_PROFILE_H
  ```

12. Include statements should be sorted and grouped. Sorted by their hierarchical
    position in the system with low level files included first. Leave an empty
    line between groups of include statements.

  ```cpp
  #include <iostream>
  #include <iomanip>

  #include <qt/qtbutton.h>
  #include <qt/qtextfield.h>

  #include "core/profiler.h"
  ```

Statements
----------
13. (?) Type conversions must always be done explicitly.

  ```cpp
  floatValue = static_cast<float>(intValue);
  ```

14. Pointers and references should have their reference symbol next to the type.

  ```cpp
  float* x; // NOT: float *x;
  int& y; // NOT: int &y;
  ```

15. Implicit test for _\0_ should not be used other than for booleans and
    pointers.

  ```cpp
  if (numLines != 0) // NOT: if (numLines)
  if (value != 0.0)  // NOT: if (value)
  ```

16. Use precision specification for floating point values unless there is an
    explicit need for double.

   ```cpp
   float f = 0.5f; // NOT: float f = 0.5;
   float f = 1.0f; // NOT: float f = 1.f;
   ```

Layouts and Comments
--------------------
###Layout

17. Basic indentation should be 2 spaces (expanded tabs).

18. Use tipically trailing braces everywhere.

  ```cpp
  if (x) {
  }
  ```

19. The _else_ statement starts on the same line as the last closing brace.

  ```cpp
  if (x) {
  } else {
  }
  ```

###Whitespace

20. Conventional operators should be surrounded by a space character.
    C++ reserved words should be followed by a white space.
    Commas, colons and semicolons should be followed by white space.

  ```cpp
  a = (b + c) * d;

  while (true) {
  }

  case 100:

  for (int i = 0; i < 10; ++i) {
  }
  ```

21. Variables in declarations should be left aligned.

  ```cpp
  AsciiFile* file;
  int        nPoints;
  float      x, y;
  ```

22. Use alignment wherever possible!

###Comments

23. Avoid using comments. The code should be self explanatory.
    Only use comments if the code can't be rewritten.

24. All comments should be written in English.

Classes
-------

25. C++ header files have _.h_ extension and source files have _.cpp_ extension.
26. Each class should be declared in a header file and defined in a source file.
27. The name of the source file should be all lowercase, matching the name of the
    class.

  ```cpp
  myclass.h
  myclass.cpp
  ```

28. The method return type should be put in the left column immediately above the
   method name.

  ```cpp
  void
  MyClass::myMethod()
  {
    ...
  }
  ```

29. Always make class methods _const_ when they do not modify any class
    variables.

  ```cpp
  int getSize() const;
  ```

30. Ordering of class variables and methods should be as follows:
  - list of friend classes
  - public variables
  - public methods
  - protected variables
  - protected methods
  - private variables
  - private methods
