CC      ?= gcc
CFLAGS  ?= -Wall -Wextra -std=gnu99 -O2
TARGET  := minsh
SRCS    := $(wildcard src/*.c)
OBJS    := $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c src/shell.h
	$(CC) $(CFLAGS) -c $< -o $@

getline: CFLAGS += -DUSE_GETLINE
getline: clean $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean getline
