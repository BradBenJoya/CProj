# CProj
C/C++ project manager inspired by Cargo.

## Usage
```cproj init [project_name]```
Creates a new folder with a git repo with the projects name. Also sets up the file structure and files.
```cproj build [path]```
Builds the project. If path is not provided it will use the current working directory.
```cproj run [path```
Builds the project like the former but also runs it.

## Building
Building CProj requires a C++ 23 compiler, CMake, and Conan 2.

Install dependencies:
```bash
conan profile detect --force
conan install . --output-folder=build --build=missing
```

Configure and compile:
```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake
cmake --build build
```
