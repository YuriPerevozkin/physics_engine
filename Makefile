CC=gcc
CFLAGS=-lraylib
SRCDIR=src

TARGET=app

SRCS=$(wildcard $(SRCDIR)/*.c $(SRCDIR)/graphics/*.c $(SRCDIR)/physics/*.c)
OBJS=$(SRCS:.c=.o)

UNAME := $(shell uname -s)
ifeq ($(findstring MINGW, $(UNAME)),MINGW)
	CFLAGS += -lopengl32 -lgdi32 -lwinmm
endif

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	rm $(TARGET)
	rm src/*.o
	rm src/graphics/*.o
