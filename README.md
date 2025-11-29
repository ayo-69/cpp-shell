# Basic Shell

This is a simple shell program written in C++. It provides a command-line interface for executing commands.

## Features

*   Execute commands with arguments
*   Change directory with `cd`
*   Set environment variables with `setenv`
*   Print environment variables with `printenv`
*   Execute commands from a file with `source`
*   Exit the shell with `exit`

## Building and Running

To build the shell, you will need a C++ compiler and CMake.

```bash
cmake .
make
```

To run the shell, execute the following command:

```bash
./shell
```

## Known Issues

* The `source` command does not handle errors in the sourced file.
* The `parse` function does not handle quotes or other special characters.
