CC=gcc
CFLAGS=-Wall -g -std=c99
objects := $(patsubst %.c,%.o,$(wildcard ./SRC/*.c))

target: $(objects)
	$(CC) -o ex26 $(objects)
	
clean:
	rm -f ex26
