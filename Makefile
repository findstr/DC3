.PHONY:all

all:dc3

dc3: dc3.c test.c
	gcc -Wall -g3 -o $@ $^

test:dc3
	./dc3
