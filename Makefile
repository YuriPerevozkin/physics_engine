CC=gcc
CFLAGS=-lraylib

run: graphics/main.o
	./$<

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
