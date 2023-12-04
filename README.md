# Minishell - As Beautiful as a Shell

## Introduction

Minishell is a project centered around creating a simple shell, akin to a basic bash. It provides an opportunity to delve into processes and file descriptors, exploring the historical significance of shells in the IT world.

## Mandatory Part

### Program: minishell

- Files: Makefile, _.h, _.c
- Makefile: NAME, all, clean, fclean, re
- Arguments: N/A
- External Functions: readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
- Libft Authorized: Yes
- Description: Write a shell with history, executable search, and redirections.

### Requirements

- Display a prompt when waiting for a new command.
- Working history functionality.
- Search and launch the right executable based on the PATH variable or using a relative/absolute path.
- Use only one global variable.
- Do not interpret unclosed quotes or unnecessary special characters.
- Handle single quotes ('), preventing interpretation of metacharacters.
- Handle double quotes (") preventing interpretation of metacharacters except for $ (dollar sign).
- Implement redirections: <, >, <<, and >>.
- Implement pipes (|) connecting command outputs.
- Handle environment variables ($ followed by a sequence of characters).
- Handle $? expanding to the exit status of the most recently executed foreground pipeline.
- Handle ctrl-C, ctrl-D, and ctrl-\ as in bash.
- Implement built-ins: echo, cd, pwd, export, unset, env, exit.
