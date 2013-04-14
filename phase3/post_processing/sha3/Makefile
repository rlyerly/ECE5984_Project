BIN=sha3_test

CC=/home/rlyerly/Projects/Android/gcc-arm/bin/arm-none-linux-gnueabi-gcc
CFLAGS=-O3 -Wall -o $(BIN) -static

INCLUDE=-I./include

SRC=$(shell ls *.c) $(shell ls src/*.c) $(shell ls src/*.s)

all: $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)

clean:
	rm $(BIN)
