#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "shell.h"

int spawn_process(char **args)
{
  int status;
  pid_t pid = fork();

  if (pid == 0) {
    if (execvp(args[0], args) == -1)
      perror("minsh");
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("minsh");
  } else {
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int run_command(char **args)
{
  int handled;
  int result;

  if (args[0] == NULL)
    return 1;

  result = try_builtin(args, &handled);
  if (handled)
    return result;

  return spawn_process(args);
}
