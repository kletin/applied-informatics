# Makefile to build and install libhelpers.a

CC = gcc
CFLAGS = -Wall -Wextra -O3 -I.
AR = ar
ARFLAGS = rcs

SRCS = strlib.c simpio.c random.c genlib.c
OBJS = $(SRCS:.c=.o)
HDRS = strlib.h simpio.h random.h genlib.h
LIB = libcpplib.a

PREFIX = ..
INCLUDEDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(LIB)
	mkdir -p $(INCLUDEDIR)
	mkdir -p $(LIBDIR)
	cp $(HDRS) $(INCLUDEDIR)
	mv $(LIB) $(LIBDIR)
	rm $(OBJS)

uninstall:
	rm -rf $(INCLUDEDIR)
	rm -rf $(LIBDIR)


clean:
	rm -f $(OBJS) $(LIB)

.PHONY: all clean install
