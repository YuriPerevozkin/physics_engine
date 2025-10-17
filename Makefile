CC=gcc
CFLAGS=-lraylib

TARGET=app.out

SRCS=$(wildcard src/*.c src/**/*.c)
OBJS=$(SRCS:.c=.o)

UNAME := $(shell uname -s)
ifeq ($(findstring MINGW, $(UNAME)),MINGW)
	CFLAGS += -lopengl32 -lgdi32 -lwinmm
endif

run: $(TARGET)
	__GLX_VENDOR_LIBRARY_NAME=mesa ./$<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	rm $(OBJS) $(TARGET)