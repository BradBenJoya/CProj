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
Building CProj is very simple. All you need is a C++ 23 compiler and CMake.
To compile run:
```cmake -S . -B build```
And:
```cmake --build build```
