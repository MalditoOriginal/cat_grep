.PHONY: all clean rebuild s21_cat

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

all: s21_cat

s21_cat: s21_cat.o
	$(CC) s21_cat.o -o s21_cat

s21_cat.o: s21_cat.c 
	$(CC) $(CFLAGS) s21_cat.c

clean:
		rm -rf *.o s21_cat

rebuild: clean all

