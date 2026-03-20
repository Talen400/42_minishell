# 🐚 Minishell

> A functional Unix shell implementation built from scratch in C, developed at [42 São Paulo](https://www.42sp.org.br/).

---

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Architecture](#architecture)
- [Pipeline](#pipeline)
- [Builtins](#builtins)
- [How to Build & Run](#how-to-build--run)
- [Usage Examples](#usage-examples)
- [Testing](#testing)
- [Authors](#authors)

---

## About

Minishell is a project from the 42 curriculum that challenges students to re-implement a simplified Unix shell — similar to `bash` — from the ground up in C, with no external parsing libraries. The goal is to deeply understand how a shell works: tokenization, parsing, variable expansion, process management, signal handling, and I/O redirection.

This implementation was developed by **fbenini-** and **tlavared** at 42 São Paulo, between November 2025 and January 2026.

---

## Features

### Mandatory

| Feature | Description |
|---|---|
| **Pipes** `\|` | Connect multiple commands, piping stdout to stdin |
| **Redirections** `<` `>` `>>` | Input/output redirection and append mode |
| **Heredoc** `<<` | Multi-line input until delimiter |
| **Variable expansion** `$VAR` | Expand environment variables |
| **`$?`** | Expand last command's exit status |
| **Quote handling** `'` `"` | Single quotes suppress all expansion; double quotes allow `$` expansion |
| **Signal handling** | `Ctrl+C`, `Ctrl+D`, `Ctrl+\` behave like bash |
| **Command history** | Via GNU Readline |

### Bonus

| Feature | Description |
|---|---|
| **Logical operators** `&&` `\|\|` | Short-circuit evaluation with left-to-right associativity |
| **Subshells** `$(cmd)` | Command substitution in arguments |
| **Wildcards** `*` | Glob expansion for filenames |
| **Tab autocomplete** | Context-aware completion for builtins, commands, and filenames |

---

## Architecture

The project is organized into distinct, well-separated modules:

```
minishell/
├── src/
│   ├── lexer/          # Tokenizer (table-driven automaton)
│   ├── parser/         # AST builder
│   ├── expander/       # Variable/wildcard expansion (table-driven automaton)
│   ├── exec/           # Execution engine (pipes, redirects, heredoc)
│   ├── builtins/       # Built-in commands
│   ├── signals/        # Signal handlers
│   └── autocomplete/   # Tab completion (bonus)
├── includes/           # Header files
├── libft/              # Custom C standard library
└── Makefile
```

---

## Pipeline

Every command the user types goes through a clear, sequential pipeline:

```
User Input (readline)
        │
        ▼
   [ LEXER ]
   Table-driven finite automaton
   Produces a linked list of tokens
   (WORD, PIPE, REDIR_IN, REDIR_OUT, HEREDOC, APPEND,
    SQUOTE, DQUOTE, EXPANSER, AND, OR, OPEN_PAR, ...)
        │
        ▼
 [ SYNTAX CHECK ]
   Validates token sequence
   (detects unclosed quotes, bad redirections, etc.)
        │
        ▼
   [ PARSER ]
   Recursive descent parser
   Builds an Abstract Syntax Tree (AST)

   parse_logical()
     └─► parse_pipeline()
           └─► parse_command()

   AST Node Types:
     • NODE_CMD     – a single command with args and redirects
     • NODE_PIPE    – a list of commands connected by pipes
     • NODE_LOGICAL – left/right subtrees with && or || operator
        │
        ▼
  [ EXPANDER ]
   Table-driven automaton walks each token's value
   States: INIT (0) | D_QUOTE (1) | S_QUOTE (2)
   Handles: $VAR, $?, $(subshell), wildcard *
   Respects quoting rules per POSIX
        │
        ▼
  [ EXECUTOR ]
   Walks the AST recursively:
     • NODE_LOGICAL → short-circuit eval
     • NODE_PIPE    → fork() per command, dup2() for pipe fds
     • NODE_CMD     → handle redirects, then run builtin or execve()
```

### Lexer — Table-Driven Automaton

The lexer uses a **finite state machine** with **10 states** and **14 character types** to tokenize raw input without backtracking. This avoids complex conditional logic and makes it straightforward to extend with new token types.

```
Character types: WSPACE, LETTER, PIPE, AND, LESS, GREATER,
                 OPEN_PAR, CLOSE_PAR, S_QUOTE, D_QUOTE,
                 DOLLAR, LBRACE, RBRACE, NUL
```

### Expander — Table-Driven Automaton

The expander also uses a finite state machine, separate from the lexer, with **3 states** and **8 character types**, to correctly handle variable expansion while respecting quoting:

```
States:
  0 (INIT)    – outside quotes
  1 (D_QUOTE) – inside double quotes: $VAR expands, 'x' is literal
  2 (S_QUOTE) – inside single quotes: everything is literal

Transition table:
          LET  "   '   $   (   )   *   \0
state 0:   0   1   2   0   0   0   0    0
state 1:   1   0   1   1   1   1   1    0
state 2:   2   2   0   2   2   2   2    0
```

### AST Node Structure

```c
// Three node types compose the entire grammar
enum e_node_type { NODE_CMD, NODE_PIPE, NODE_LOGICAL };

typedef struct s_ast_node {
    int type;
    union {
        t_cmd_node     cmd;     // command + args + redirections
        t_pipe_node    pipe;    // array of NODE_CMD children
        t_logical_node logical; // left, right, operator (&&/||)
    } u_data;
} t_ast_node;
```

Each `t_expandable_value` (an argument or redirect target) stores both the `raw` token string and the `processed` (post-expansion) string, keeping the two phases cleanly separated.

---

## Builtins

The following builtins are implemented natively (no `execve`):

| Builtin | Behavior |
|---|---|
| `echo [-n]` | Print arguments to stdout; `-n` suppresses trailing newline |
| `cd <path>` | Change current directory via `chdir()` |
| `pwd` | Print current working directory |
| `env` | Print all environment variables |
| `export [KEY=VALUE]` | Set or display environment variables |
| `unset KEY` | Remove an environment variable |
| `exit [code]` | Exit with optional numeric status code |

Builtins that affect the shell state (like `cd`, `export`, `unset`) are executed directly in the parent process. Inside a pipe, they are executed in a child process like any other command.

---

## How to Build & Run

### Prerequisites

- `gcc` or `cc`
- GNU `readline` library
- `make`

On Debian/Ubuntu:
```bash
sudo apt-get install libreadline-dev
```

### Build

```bash
# Build the mandatory version
make

# Build the bonus version (autocomplete, &&/||, subshells)
make bonus

# Clean object files
make clean

# Full clean (including binary)
make fclean

# Rebuild from scratch
make re
```

### Run

```bash
./minishell
```

### Valgrind (leak check)

The Makefile includes a built-in valgrind target with readline suppressions:

```bash
make val
```

---

## Usage Examples

```bash
# Basic command
minishell$ ls -la

# Pipes
minishell$ cat file.txt | grep "hello" | wc -l

# Redirections
minishell$ ls > output.txt
minishell$ cat < input.txt >> log.txt

# Heredoc
minishell$ cat << EOF
> Hello
> World
> EOF

# Variable expansion
minishell$ echo $HOME
minishell$ echo "Exit status: $?"

# Single vs double quotes
minishell$ echo '$HOME'         # prints: $HOME
minishell$ echo "$HOME"         # prints: /home/user

# Logical operators (bonus)
minishell$ mkdir test && cd test
minishell$ cat missing.txt || echo "File not found"

# Command substitution (bonus)
minishell$ echo "Today is $(date)"

# Wildcard (bonus)
minishell$ echo *.c

# Builtins
minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
minishell$ unset MY_VAR
minishell$ exit 0
```

---

## Testing

A bash comparison test script is included. It runs each test command through both `bash` and `minishell`, compares stdout output and exit codes, and reports `[OK]` / `[KO]`. Memory leaks are detected via `valgrind` and flagged separately.

```bash
bash test.sh
```

Test cases cover:
- Variable expansion edge cases (`$PWD`, `$EMPTY`, `$?`)
- All redirect combinations (`<`, `>`, `>>`, `<<`) including permission errors and missing files
- Pipe + redirect interactions
- `export` / `cd` / `exit` argument validation
- Quoted redirections (`cat <"file"`)

---

## Authors

| Login | GitHub |
|---|---|
| **fbenini-** | 42 São Paulo |
| **tlavared** | 42 São Paulo |

---

*Built as part of the 42 Common Core curriculum.*
