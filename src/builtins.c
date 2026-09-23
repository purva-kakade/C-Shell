#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"

static char *builtin_names[] = {
  "cd",
  "help",
  "exit"
};

static int (*builtin_handlers[])(char **) = {
  &cmd_cd,
  &cmd_help,
  &cmd_exit
};

int builtin_count(void)
{
  return sizeof(builtin_names) / sizeof(char *);
}

int try_builtin(char **args, int *handled)
{
  for (int i = 0; i < builtin_count(); i++) {
    if (strcmp(args[0], builtin_names[i]) == 0) {
      *handled = 1;
      return builtin_handlers[i](args);
    }
  }
  *handled = 0;
  return 1;
}

int cmd_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "minsh: expected argument to \"cd\"\n");
  } else if (chdir(args[1]) != 0) {
    perror("minsh");
  }
  return 1;
}

int cmd_help(char **args)
{
  (void)args;
  printf("minsh - a minimal shell\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (int i = 0; i < builtin_count(); i++)
    printf("  %s\n", builtin_names[i]);

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int cmd_exit(char **args)
{
  (void)args;
  return 0;
}
