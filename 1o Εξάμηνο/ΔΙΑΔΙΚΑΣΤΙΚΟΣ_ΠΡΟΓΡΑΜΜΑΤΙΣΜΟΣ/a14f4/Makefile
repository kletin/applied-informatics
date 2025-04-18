# Makefile to build a2f9 using local cpplib

CC = gcc
CPPLIB = ../cpplib
CFLAGS = -I${CPPLIB}/include -g -Wall -O3
LDLIBS = -L${CPPLIB}/lib -lcpplib -lm

DIRNAME := $(shell basename "$(CURDIR)")
SRC = $(DIRNAME).c
OUT = $(DIRNAME)

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -rf $(OUT) *.dSYM

.PHONY: all clean test
