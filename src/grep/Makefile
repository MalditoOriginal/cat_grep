.PHONY: all clean rebuild s21_grep

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

all: s21_grep

s21_grep: s21_grep.o
	$(CC) s21_grep.o -o s21_grep

s21_grep.o: s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c

clean:
		rm -rf *.o s21_grep

rebuild: clean all