CC      = clang
CFLAGS  = -std=c99 -Wall -Wextra -O2 -Iinclude

SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:.c=.o)
TARGET  = test_runner

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)
