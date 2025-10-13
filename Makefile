CC=gcc
CFLAGS=-lraylib

run: main.o
	./$<

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
