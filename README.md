# minsh

A small Unix shell written in C. It covers the basic loop every shell runs:
read a line, split it into arguments, then either run a builtin or fork and
exec the program and wait for it to finish.

## Build

```
make
./minsh
```

To use the `getline()`-based input reader instead of the manual one:

```
make getline
```

## Builtins

- `cd <dir>`
- `help`
- `exit`

## Limitations

- One command per line
- Arguments are split on whitespace only
- No quoting or escaping
- No pipes or redirection

## Layout

```
src/
  main.c      entry point and the read/eval loop
  input.c     reading a line and splitting it into tokens
  exec.c      running builtins or launching programs
  builtins.c  cd, help, exit
  shell.h     shared declarations
```

## License

Public domain, see [UNLICENSE](UNLICENSE).
