# ──────────────────────────────────────────────────────────────
# Perfect development Makefile for modular-crypto-lib
# ──────────────────────────────────────────────────────────────
CC      = clang
CFLAGS  = -std=c99 -Wall -Wextra -Werror -O2 -Iinclude     # ← -Werror is golden here
AR      = ar
ARFLAGS = rcs

# All source files
SRC = $(wildcard src/*.c)

# Object files (one per .c)
OBJ = $(SRC:.c=.o)

# Final targets
STATIC_LIB = libmcrypto.a          # ← this is what you really want later
CHECK      = build-check           # ← dummy target just to test compilation

# Default goal: just test that everything compiles cleanly
all: $(CHECK)

# Rule 1: Test compilation — this is what you want right now
$(CHECK): $(OBJ)
	@echo "────────────────────────────────────"
	@echo "All files compiled successfully! No errors."
	@echo "────────────────────────────────────"
	@touch $@                     # create a timestamp file

# Rule 2: How to build .o files from .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule 3: (Optional) Build static library when you're ready
$(STATIC_LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^
	@echo "Static library built: $@"

# Clean everything
clean:
	rm -f $(OBJ) $(STATIC_LIB) $(CHECK)
	@echo "Clean done."

# Mark these as not real files
.PHONY: all clean lib check
# ──────────────────────────────────────────────────────────────
