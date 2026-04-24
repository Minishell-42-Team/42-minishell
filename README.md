
<p align="center">
*This project has been created as part of the 42 curriculum by cwenhaj and vnaoussi.*
</p>

# <h1 align="center">*MINISHELL*</h1>
### Description
**Minishell** is a simplified Unix shell inspired by Bash.

The goal of this project is to understand how a shell works internally by implementing core features such as:

- command parsing
- process creation and management
- pipes and redirections
- environment variables
- signal handling

The program **reads user input, processes it through several stages (lexing, parsing, expansion), and executes commands** using low-level system calls.

### Features

- Execution of basic commands (ls, cat, etc.)
- Builtins: cd, echo, pwd, export, unset, env, exit
- Pipes ( | )
- Redirections (<, >, >>, <<)
- Environment variable expansion (`$VAR`, `$?`)
- Wildcard expansion (*)
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+`\`)

### Architecture Overview

The shell follows this pipeline:

INPUT → LEXER → EXPANDER → PARSER → EXECUTION

- **Lexer**: splits input into tokens
- **Expander**: resolves environment variables
- **Parser**: builds a command structure (AST-like)
- **Execution**: handles pipes, forks, and command execution

### Instructions

1. <u>**Compilation:**</u> 

The program must compile with 42 mandatory flags: -Wall -Werror -Wextra

Makefile usual commands:

```bash
make        # Compiles
make clean  # Deletes objs
make fclean # Deletes objs and executable
make re     # Cleans and recompiles
```

### Resources

<u>**Documentation & References**</u>

- [Bash Reference Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.pdf)
- [General Overview 1](https://medium.com/@gibrat.dylan/minishell-42-lart-de-cr%C3%A9er-un-shell-performant-et-maintenable-53c0aede140e)
- [General Overview 2](https://www.notion.so/minishell-quelques-vieilles-astuces-de-grand-m-re-2fe0b3dc40f280c88099cb289a9210c3)
- [General Overview 3](https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b)
- [General Commands](https://docs.google.com/spreadsheets/d/1FxfG_p_mxK8eFPgqDhq_4E8PlybEdM_MNZgGnfBHZHE/edit?gid=0#gid=0)
- [Readme Syntax](https://markdownguide.offshoot.io/basic-syntax/) - to understand how to write a readme
- Unix manual pages (man 2 fork, man 2 execve, man 2 pipe, man 2 dup2)

<u>**AI**</u> has been used to:
- Clarifying concepts related to process management and file descriptors
- Understanding edge cases in parsing and expansion
- Assisting in debugging specific issues
- test all possible cases

* <u>**Notes**</u>
- The project focuses on reproducing core shell behavior, not full Bash compatibility
- Some advanced features (like &&, ||, or subshells) are not implemented.

* <u>**Memory Management**</u>
- All allocated memory is properly freed
- No memory leaks (tested with valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s)

* <u>**Signals**</u>
- Ctrl+C → interrupts current input and displays a new prompt
- Ctrl+\ → ignored
- Ctrl+D → exits the shell (EOF), displaying exit

 <u>**readline.supp**</u> file was also used **to ignore false-positive memory leaks** caused by the GNU Readline library when using tools like Valgrind. By using this file, only **real leaks from our code** are shown. 

valgrind --suppressions=readline.supp ./minishell

