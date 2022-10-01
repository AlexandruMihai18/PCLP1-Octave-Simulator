CC=gcc
CFLAGS=-Wall -Wextra -std=c99

build:
	$(CC) $(CFLAGS) *.c -o my_octave
	
clean:
	rm -f my_octave

