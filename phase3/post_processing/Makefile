BIN=pp

CC=/home/rlyerly/Projects/Android/gcc-arm/bin/arm-none-linux-gnueabi-gcc
CFLAGS=-O3 -Wall -o $(BIN) -static

INCLUDE=-I./include -I./sha3/include

LIBS=-lm
LDFLAGS=

SRC=$(shell ls *.c) $(shell ls src/*.c) $(shell ls sha3/src/*.c) \
		$(shell ls sha3/src/*.s)

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) $(SRC) $(LIBS)

clean:
	rm $(BIN)
