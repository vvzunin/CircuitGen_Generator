# Coding style

This document summarizes the main coding rules for this project:

1. Use LF line endings in source files (`.cpp`, `.h`, …).
2. Base indent is 2 spaces. TAB characters are not allowed.
3. Maximum line length is 80 characters.
4. Do not use multiple consecutive blank lines.
5. Use UpperCamelCase for class / enum / struct / type / union names.
6. Use lowerCamelCase for function / method / object names.
7. Use prefix_lowerCamelCase for variables: `d_` for class fields, `i_` for method parameters.
8. Place `{` on the same line as the corresponding statement.
9. All class headers, methods, and other functions must include Doxygen-style comments.
10. Order `#include` directives as follows:
   - project headers;
   - third-party libraries;
   - system libraries.

Within each group, sort includes alphabetically.

**Русский:** [Стиль кодирования](../ru/CodeStyle.md)
