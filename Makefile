CC=gcc
CFLAGS=-Wall -g -std=c99 -DNDEBUG
objects := $(patsubst %.c,%.o,$(wildcard ./SRC/*.c))

target: $(objects)
	$(CC) $(CFLAGS) -o ex26 $(objects) 
	
clean:
	rm -f ex26

clean_all: clean
	rm ./SRC/*.o