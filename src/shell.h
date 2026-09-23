#ifndef MINSH_SHELL_H
#define MINSH_SHELL_H

#define READ_BUF_SIZE 1024
#define TOKEN_BUF_SIZE 64
#define TOKEN_DELIMS " \t\r\n\a"

char *read_input(void);
char **tokenize(char *line);

int run_command(char **args);
int spawn_process(char **args);

int builtin_count(void);
int try_builtin(char **args, int *handled);

int cmd_cd(char **args);
int cmd_help(char **args);
int cmd_exit(char **args);

#endif
