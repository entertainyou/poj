CFLAGS=-g -Wall

default: test

build:
	gcc $(CFLAGS) -o $(target) $(target).c

test: build
	cat $(target).input | ./$(target)

