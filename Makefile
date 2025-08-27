# Compiler and flags
CC = gcc
CFLAGS = -std=c17 -Wall -Wextra
DEBUGFLAGS = -g -O0

# Executable name
TARGET = cndnd

# Source files
SRCS = main.c character.c bestiary.c combat.c dicegoblin.c

# Object files (replace .c with .o)
OBJS = $(SRCS:.c=.o)

# Default: build normally
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build (adds -g -O0)
debug: CFLAGS += $(DEBUGFLAGS)
debug: clean $(TARGET)

# Cleanup rule
clean:
	rm -f $(OBJS) $(TARGET)
