SRC     = ./src
LIB     = ./include
BUILD   = ./build

CC      = g++
CFLAGS  = -Wall -I $(LIB) -std=c++11

LD      = g++
LDFLAGS = -Wall -I $(LIB) -std=c++11

OBJ		= $(BUILD)/main.o $(BUILD)/option.o $(BUILD)/debug.o

default:
	@echo "Please write the option properly"

# Make build directory
$(BUILD):
	mkdir -p $(BUILD)

# Compiler 
compiler:
	$(CC) $(CFLAGS) -c -o $(BUILD)/$(TARGET).o $(SRC)/$(TARGET).cpp

$(BUILD)/main.o:
	make compiler TARGET=main

$(BUILD)/option.o:
	make compiler TARGET=option

$(BUILD)/debug.o:
	make compiler TARGET=debug

# Linker
main:
	$(LD) $(LDFLAGS) -o main $(OBJ)

# clean
clean:
	rm -f main
	rm -rf build

# execute
execute:
	./main

# All
all: clean $(BUILD) $(OBJ) main