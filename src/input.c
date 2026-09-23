#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

static void alloc_fail(void)
{
  fprintf(stderr, "minsh: allocation error\n");
  exit(EXIT_FAILURE);
}

#ifdef USE_GETLINE
char *read_input(void)
{
  char *line = NULL;
  size_t cap = 0;

  if (getline(&line, &cap, stdin) == -1) {
    if (feof(stdin))
      exit(EXIT_SUCCESS);
    perror("minsh: getline\n");
    exit(EXIT_FAILURE);
  }
  return line;
}
#else
char *read_input(void)
{
  int cap = READ_BUF_SIZE;
  int len = 0;
  char *buf = malloc(sizeof(char) * cap);
  int ch;

  if (!buf)
    alloc_fail();

  while (1) {
    ch = getchar();

    if (ch == EOF) {
      exit(EXIT_SUCCESS);
    } else if (ch == '\n') {
      buf[len] = '\0';
      return buf;
    } else {
      buf[len] = ch;
    }
    len++;

    if (len >= cap) {
      cap += READ_BUF_SIZE;
      buf = realloc(buf, cap);
      if (!buf)
        alloc_fail();
    }
  }
}
#endif

char **tokenize(char *line)
{
  int cap = TOKEN_BUF_SIZE;
  int count = 0;
  char **tokens = malloc(cap * sizeof(char *));
  char **old;
  char *tok;

  if (!tokens)
    alloc_fail();

  tok = strtok(line, TOKEN_DELIMS);
  while (tok != NULL) {
    tokens[count++] = tok;

    if (count >= cap) {
      cap += TOKEN_BUF_SIZE;
      old = tokens;
      tokens = realloc(tokens, cap * sizeof(char *));
      if (!tokens) {
        free(old);
        alloc_fail();
      }
    }

    tok = strtok(NULL, TOKEN_DELIMS);
  }
  tokens[count] = NULL;
  return tokens;
}
