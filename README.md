# Minishell
## 📖 Description

Minishell is a minimalistic recreation of a UNIX shell. It implements core features, like parsing, command execution, signal handling, and environment management, redirections, pipes, and built-in commands, ... This is a 2-person group project, developed to gain a deeper understanding of how shells work internally by building one from scratch in C.

## 🚀 Features

- Prompt display and user input handling
- Built-in commands:
    - `echo`
    - `cd`
    - `pwd`
    - `export`
    - `unset`
    - `env`
    - `exit`

- Execution of external commands using `$PATH`
- Pipes (`|`) to chain commands
- Quote handeling (single and double quotes)
- Input and output redirection (`<`, `>`, `>>`)
- Here-document support (`<<`)
- Managed and expand environment variable (`$VARIABLE`)
- Signal handling (`Ctrl+C`, `Ctrl+\`)
- Error management with proper exit codes
- Memory management (no leaks!)

## 🧪 Bonus Features 
In addition we also implemented:
- Wildcard expansion (`*`)
- Logical operators (`&&`, `||`)
- Command history

## 🔨 Built-in Commands
Command	Description
- `cd`	    Changes the current directory.
- `pwd`	    Prints the current working directory.
- `echo`	Prints arguments to standard output.
- `env`	    Prints environment variables.
- `export`	Sets environment variables.
- `unset`	Unsets environment variables.
- `exit`    Exit the shell.

## ⚙️ Installation
### Requirement
- Unix-like environment (Linux, macOS)
- GCC
- Make


### Compilation
1. Clone the project 
``` Shell
git clone git@github.com:hetya/Minishell.git
```
2. Compile it using make
``` Shell
make
```

## 🖥️ Usage
``` Shell
./minishell
```

Then you can use it like a normal shell
``` Shell
Finishell > echo test
Finishell > ls -la | grep minishell > output.txt
Finishell > export foo=bar
Finishell > exit
```
