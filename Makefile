#Eli Cuala Assignment 2 Lec A2 Lab D06 \
ccid: cuala \
Student ID: 1898248 \
Instructor: Henry Tang

CC = gcc
CFLAGS = -Wall -Werror -std=c99

assg : src/assg.c src/assg.h
	$(CC) $(CFLAGS) -o assg src/assg.c

clean:
	rm -f assg