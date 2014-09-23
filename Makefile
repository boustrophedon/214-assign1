CC=clang
CFLAGS=-Wall -Werror -g
LDFLAGS=-g

all: tokenizer

tokenizer: tokenizer.o parse.o
		$(CC) $(LDFLAGS) tokenizer.o parse.o -o tokenizer

tokenizer.o: tokenizer.c
		$(CC) $(CFLAGS) -c tokenizer.c

parse.o: parse.c
		$(CC) $(CFLAGS) -c parse.c

clean:
	rm tokenizer
	rm *o
