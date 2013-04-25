# Names of binaries
HEX2BIN=hex_2_bin
THROWAWAY_STATIC=throwaway_bits_static
BIN=$(HEX2BIN) $(THROWAWAY_STATIC)

# General compiler flags
CC=gcc
CFLAGS=-O3 -Wall
DEBUG=-g

# Sources
HEX2BIN_SRC=$(shell ls hex2bin/*.c)
THROWAWAY_STATIC_SRC=$(shell ls throwaway_static/*.c)

all: $(BIN)

$(HEX2BIN): $(HEX2BIN_SRC)
	$(CC) -o $@ $(CFLAGS) $<

$(THROWAWAY_STATIC): $(THROWAWAY_STATIC_SRC)
	$(CC) -o $@ $(CFLAGS) $<

clean:
	rm -f $(BIN)
