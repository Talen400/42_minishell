# minishell 🐢

Minishell is a project from 42 School Common Core curriculum. It consists on creating a shell with basic features.

This project supports the following features:

### Basic command execution

```bash
echo hello
```

### Input and output redirection

```bash
< infile cat -e > outfile
<< heredoc cat >> out_append
```

### Pipes

```bash
ls -l | cat -e | wc -l
```

### Logical operators with parenthesis

```bash
echo oi && false || echo "execute on fail"
(ls / && (echo interno && false)) || echo 'externo'
```

### Wildcards and envvars expansion

```bash
cc -Wall -Wextra -Werror *.c
echo $PWD
echo $SHLVL
echo $?
echo */*
```
