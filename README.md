# Ccat

**Ccat** is a lightweight C-based program that reads text files and displays their content in a formatted way, similar to `cat`, but with additional features like line numbering, word counting, and more.

---

## Features

- **Formatted Output**: Displays file content with line numbers and a file header.
- **Character Count (`--ca`)**: Shows the number of characters in the file (excluding spaces).
- **Word Count (`--cw`)**: Shows the total number of words in the file.
- **Line Count (`--cl`)**: Displays the number of lines in the file.
- **Help (`--help`)**: Provides detailed usage instructions and examples.

---

### Compilation

To compile the program, use the following command:
```bash
gcc -o ccat ccat.c
```

### Command Format
```bash
./ccat [OPTIONS] <filename1> [filename2 ...]
```
