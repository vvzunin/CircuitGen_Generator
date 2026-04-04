# Hacking

Tips for building and testing this project as a developer or contributor.

## Developer mode

Developer-only CMake targets stay hidden unless `CircuitGenGenerator_DEVELOPER_MODE` is enabled. Turning it on exposes tests and other dev-only options. If you leave it off, you are a consumer of the library and do not need those targets.

Developer mode is always enabled in CI workflows.

### Naming conventions

- `d_*` — class fields;
- `i_*` — function parameters.

### Presets

This project uses [CMake presets][1]. Install the [latest CMake][2] to get the best experience.

You can pass `CircuitGenGenerator_DEVELOPER_MODE` in several ways; this repo prefers presets.

There are two levels:

- `CMakePresets.json` — shared project presets (CI, release, hidden base presets), tracked in git;
- `CMakeUserPresets.json` — local developer presets (`dev`, `coverage`, `dev-msvc`), **not** tracked.

`CMakeUserPresets.json` is gitignored; create it after clone:

```sh
cp CMakeUserPresets.json.example CMakeUserPresets.json
```

If the example file is missing, author `CMakeUserPresets.json` manually from `CMakePresets.json` and the docs. You can extend it with local tool paths and cache variables without touching CI commands.

> **Note**
> Some IDEs aggressively auto-configure preset-based projects.
> Make sure your editor only configures when you intend it to — e.g. in CLion, enable only the `dev` profile under
> `File > Settings > Build, Execution, Deployment > CMake`; in Visual Studio, set CMake to **never** run the configure step automatically under
> `Tools > Options > CMake` **before** opening the project, then configure manually via **Project > Configure Cache**.

### Configure, build, test

From the repo root:

```sh
cmake --preset=dev
cmake --build --preset=dev
ctest --preset=dev
```

Coverage on Linux/macOS:

```sh
cmake --preset=coverage
cmake --build --preset=coverage
ctest --preset=coverage
cmake --build --preset=coverage -t coverage
```

VSCode, CLion, Visual Studio, and similar tools can use the same user presets.

Both build and test commands accept `-j` for parallelism; match it to your CPU count or set `jobs` in a preset (see the [preset documentation][1]).

### Developer targets

Pass `-t <target>` to the build command:

#### `coverage`

Available when `ENABLE_COVERAGE` is on. Aggregates coverage with `lcov`, writes `coverage.info` and a summary in the build tree. With `COVERAGE_ENABLE_HTML=ON`, also emits an HTML report.

#### `docs`

Available when `BUILD_MCSS_DOCS` is on. Builds Doxygen + m.css documentation for **one** language into `<binary-dir>/docs` (see `DOXYGEN_OUTPUT_DIRECTORY` and `DOXYGEN_DOCUMENTATION_LANGUAGE`). For **English and Russian** in `<binary-dir>/docs/{html,xml,latex,pdf}/{en,ru}/`, use **`scripts/dev/build-docs.sh`** (does not require this option).

#### `format-check` and `format-fix`

Run `clang-format` across the tree for verification or in-place fixes. Controlled by `FORMAT_PATTERNS` and `FORMAT_COMMAND`.

#### `run-exe`

Runs the `CircuitGenGenerator_exe` executable.

#### `spell-check` and `spell-fix`

Run the spelling tool for verification or fixes. Controlled by `SPELL_COMMAND`.

[1]: https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html
[2]: https://cmake.org/download/

### Code documentation rules

1. Descriptions, comments, and TODOs live in `.hpp` files.
2. Wrap documentation in `///` lines.
```hpp
#include <iostream>

///
///
///
```
3. Place TODOs after includes. Optionally mention the author before `@file`.
```hpp
#include <iostream>

/// @author <Author name>
/// @file <file.hpp>
/// TODO: <description>

```
4. Use `@brief` for functions and methods.
```hpp
#include <iostream>

/// @file <file.hpp>
/// TODO: <description>

/// @brief sum
/// <Function description>

int sum (int a, int b);

int main()
{
    
}

```
5. For classes and namespaces, document with `class` / `namespace` lines.
```hpp
/// namespace AuxMethods
/// <Namespace description>

namespace AuxMethods
{
    ...
}


/// class Graph
/// <Class description>

class Graph
{
    ...
}
```
6. Document parameters with `@param <name> <description>`.
**Full class example**
```hpp

/// class Graph
/// <Class description>
/// @param v
/// <Parameter description>
/// @param adj
/// <Parameter description>

class Graph
{
private:
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices)
    {
        V = vertices;
        adj.resize(V);
    }
    
    /// @brief addEdge
    /// <Method description>
    /// @param v <Parameter description>
    /// @param w <Parameter description>
    
    void addEdge(int v, int w);

};
```
7. Return values: `@return`.
```hpp
/// @brief getAdjacencyList
/// <Method description>
/// @param v
/// <Parameter description>
/// @return <Return value description>
    vector<int> getAdjacencyList(int v) const
    {
        return adj[v];
    }
```
8. Exceptions: `@throw`.
```hpp
#include <iostream>
#include <stdexcept>

/// @brief Divides two numbers.
/// If the divisor is zero, throws std::runtime_error.

/// @param dividend Dividend.
/// @param divisor Divisor.
/// @return double Quotient.
///
/// @throw runtime_error If the divisor is zero.

double divide(double dividend, double divisor)
{
    if (divisor == 0) {
        throw runtime_error("Division by zero");
    }
    return dividend / divisor;
}
```
9. Embed sample code with `@code` / `@endcode`.
**Full function example**
```
#include <iostream>
#include <stdexcept>

/// @brief Divides two numbers.
/// 
/// If the divisor is zero, throws std::runtime_error.

/// @param dividend Dividend.
/// @param divisor Divisor.
/// @return double Quotient.
/// @code
/// double a = 10.0;
/// double b = 2.0;
/// double result = divide(a, b); // result is 5.0
/// @endcode
/// @throw runtime_error If the divisor is zero.

double divide(double dividend, double divisor)
{
    if (divisor == 0) {
        throw runtime_error("Division by zero");
    }
    return dividend / divisor;
}
```
10. Cross-references: `@see <name>`.
11. Enumerations: use `@brief` and document each enumerator.
**Enum example**
```
/// @brief VertexTypes
/// Enumeration of vertex types

enum VertexTypes { ///  input vertex
  input,           ///  output vertex
  output,          /// constant vertex
  constant,        /// vertex representing a logical element
  gate,            /// subgraph that makes up the vertex
  subGraph   
};
```

**Русский:** [HACKING](../ru/HACKING.md)
