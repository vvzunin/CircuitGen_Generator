# Editor setup (VS Code)

Steps that help before working on this project in VS Code.

## IntelliSense / syntax

Recommended extensions:

- **C/C++ Extension Pack**
- **CMake Language Support**
- **WSL** (if you use WSL)

If IntelliSense mis-parses code, run **C/C++: Edit Configurations (UI)** and set:

- **Compiler path** (e.g. `/usr/bin/g++`)
- **Include path**: `${workspaceFolder}/**`
- A matching **C++ standard**

Changes land in `.vscode/c_cpp_properties.json`.

## Clang-format and `settings.json`

If `.clang-format` is missing or invalid, the editor may fall back to `.vscode/settings.json`. Point `C_Cpp.clang_format_fallbackStyle` at your project style (this repo uses an 80-column limit; see root `.clang-format`).

**Русский:** [Format.md](../ru/Format.md)
