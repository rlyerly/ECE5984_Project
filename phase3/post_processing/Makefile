LIB=libpp.a
TEST=pp_test

BUILD=build/

CC=/home/rlyerly/Projects/Android/gcc-arm/bin/arm-none-linux-gnueabi-gcc
CFLAGS=-O3 -Wall
DEBUG=-g

AR=/home/rlyerly/Projects/Android/gcc-arm/bin/arm-none-linux-gnueabi-ar
LIBFLAGS=-o $(LIB) -rcs

INCLUDE=-I./include -I./sha3/include

LIBS=-lm -lpp
LDFLAGS=-L.

# Source files
DRIVER_SRC=$(shell ls *.c)
PP_SRC=$(shell ls src/*.c)
SHA3_SRC=$(shell ls sha3/src/*.c)
SHA3_ASM=$(shell ls sha3/src/*.s)

# Object files
DRIVER_OBJ=$(addprefix $(BUILD),$(DRIVER_SRC:.c=.o))
PP_OBJ=$(addprefix $(BUILD), $(subst src/,,$(PP_SRC:.c=.o)))
SHA3_OBJ=$(addprefix $(BUILD), $(subst sha3/src/,,$(SHA3_SRC:.c=.o)))
SHA3_OBJ+=$(addprefix $(BUILD), $(subst sha3/src/,,$(SHA3_ASM:.s=.o)))

LIB_OBJ=$(PP_OBJ) $(SHA3_OBJ)

# Recipes for compiling sources TODO cleanup
$(BUILD)%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(BUILD)%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(BUILD)%.o: sha3/src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(BUILD)%.o: sha3/src/%.s
	$(CC) $(CFLAGS) -o $@ -c $<

# Recipe to build the library (static)
lib: $(LIB_OBJ)
	mkdir $(BUILD)
	$(AR) $(LIBFLAGS) $(LIB_OBJ)

# Recipe for library test
test: lib
	$(CC) -o $(TEST) $(CFLAGS) $(DEBUG) $(INCLUDE) $(LDFLAGS) $(DRIVER_SRC) $(LIBS)

all: lib test

clean:
	rm -f $(LIB)
	rm -f $(TEST)
	rm -f $(BUILD)*.o
