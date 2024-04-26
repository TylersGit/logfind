CFLAGS=-Wall -g -std=c99
objects := $(patsubst %.c,%.o,$(wildcard ./SRC/*.c))

target: $(objects)
	cc -o ex26 $(objects)
	
clean:
	rm -f ex26
