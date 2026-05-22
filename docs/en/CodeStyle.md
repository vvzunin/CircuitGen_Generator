# Coding style

This document defines the extended coding style used across CircuitGen
repositories. It keeps the same core meaning as the Russian version and adds
practical guidance.

## Core rules

1. Use LF line endings in source files (`.cpp`, `.h`, `.hpp`, ...).
2. Base indentation is 2 spaces. TAB characters are not allowed.
3. Maximum line length is 80 characters.
4. Do not use multiple consecutive blank lines.
5. Use `UpperCamelCase` for class, enum, struct, type, and union names.
6. Use `lowerCamelCase` for function, method, and object names.
7. Use `prefix_lowerCamelCase` for variables:
   - `d_` for class fields;
   - `i_` for function/method parameters.
8. Place `{` on the same line as the related statement/signature.
9. Public APIs and key functions must include Doxygen comments.
10. Order `#include` directives as follows:
    - project headers;
    - third-party libraries;
    - system headers.

Within each group, sort includes alphabetically.

## Additional requirements

- All compiler warnings must be fixed before merging into the main branch.
- Style-only edits must not change behavior.

## Documentation rules (Doxygen)

The rules below expand rule 9 from the core list.

1. Keep API descriptions and TODO notes in `.hpp` files near declarations.
2. Use `///` for documentation comments.
3. Use `@brief` for functions/methods.
4. Document parameters via `@param <name> <description>`.
5. Document return values via `@return`.
6. Document thrown exceptions via `@throw`.
7. Use `@code ... @endcode` for examples.
8. Use `@see` for cross-references.
9. For enums, use `@brief` and describe enumerators.

Short example:

```hpp
/// @brief Divides two numbers.
/// @param i_dividend Dividend.
/// @param i_divisor Divisor.
/// @return Division result.
/// @throw std::runtime_error If i_divisor == 0.
double divide(double i_dividend, double i_divisor);
```

## Detailed documentation examples

### Full class documentation

```hpp
/// @brief Graph.
/// @details Example class layout for Doxygen documentation.
class Graph
{
private:
  int d_verticesCount;
  std::vector<std::vector<int>> d_adj;

public:
  /// @brief Creates a graph with a fixed number of vertices.
  /// @param i_verticesCount Number of vertices.
  explicit Graph(int i_verticesCount)
      : d_verticesCount(i_verticesCount), d_adj(i_verticesCount)
  {
  }

  /// @brief Adds an edge.
  /// @param i_from Source vertex.
  /// @param i_to Destination vertex.
  void addEdge(int i_from, int i_to);
};
```

### Full function documentation with `@code`

```hpp
#include <stdexcept>

/// @brief Divides two numbers.
/// @param i_dividend Dividend.
/// @param i_divisor Divisor.
/// @return Quotient.
/// @code
/// double result = divide(10.0, 2.0); // 5.0
/// @endcode
/// @throw std::runtime_error If divisor is zero.
double divide(double i_dividend, double i_divisor)
{
  if (i_divisor == 0.0)
  {
    throw std::runtime_error("Division by zero");
  }
  return i_dividend / i_divisor;
}
```

### Enum example with enumerator comments

```hpp
/// @brief Graph vertex types.
enum class VertexType
{
  Input,    ///< Circuit input.
  Output,   ///< Circuit output.
  Constant, ///< Constant value.
  Gate,     ///< Logic gate.
  SubGraph  ///< Hierarchical subgraph.
};
```

### Cross-reference example

```hpp
/// @brief Builds topological order.
/// @see Graph::addEdge
void buildTopologicalOrder();
```

**Русский:** [Стиль кодирования](../ru/CodeStyle.md)
