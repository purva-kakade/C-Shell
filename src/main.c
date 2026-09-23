#include <stdio.h>
#include <stdlib.h>

#include "shell.h"

static void repl(void)
{
  char *line;
  char **args;
  int keep_going;

  do {
    printf("> ");
    line = read_input();
    args = tokenize(line);
    keep_going = run_command(args);

    free(line);
    free(args);
  } while (keep_going);
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  repl();
  return EXIT_SUCCESS;
}
