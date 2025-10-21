CC=gcc
CFLAGS=-lraylib -lm 

TARGET=app.out

SRCS:=$(shell find src -name '*.c')
OBJS:=$(patsubst %.c, %.o, $(SRCS))

TESTS_TARGET=tests.out

TESTS_SRCS:=$(shell find tests -name '*.c')
TESTS_OBJS:=$(patsubst %.c, %.o, $(TESTS_SRCS))

UNAME:=$(shell uname -s)
ifeq ($(findstring MINGW, $(UNAME)),MINGW)
	CFLAGS += -lopengl32 -lgdi32 -lwinmm
endif

ifeq ($(findstring Darwin, $(UNAME)),Darwin)
	CFLAGS += $(shell pkg-config --cflags --libs raylib)
endif

.PHONY: run clean test

run: $(TARGET)
	__GLX_VENDOR_LIBRARY_NAME=mesa ./$<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

test: $(TESTS_TARGET)
	./$<

$(TESTS_TARGET): $(TESTS_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS) $(TESTS_OBJS) $(TARGET) $(TESTS_TARGET)
