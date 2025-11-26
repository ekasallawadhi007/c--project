
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRCS = src/main.c src/book.c
TARGET = library.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

.PHONY: clean
clean:
	-rm -f $(TARGET) *.o library.dat
