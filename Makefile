CC      = clang
CFLAGS  = -std=c99 -Wall -Wextra -O2 -Iinclude

SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:.c=.o)
TARGET  = crypto_utils

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)
