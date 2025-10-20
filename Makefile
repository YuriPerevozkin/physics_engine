CC=gcc
CFLAGS=-lraylib -lm

TARGET=app.out

SRCS:=$(shell find src -name '*.c')
OBJS:=$(patsubst %.c, %.o, $(SRCS))

UNAME:=$(shell uname -s)
ifeq ($(findstring MINGW, $(UNAME)),MINGW)
	CFLAGS += -lopengl32 -lgdi32 -lwinmm
endif

.PHONY: run clean

run: $(TARGET)
	__GLX_VENDOR_LIBRARY_NAME=mesa ./$<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS) $(TARGET)
