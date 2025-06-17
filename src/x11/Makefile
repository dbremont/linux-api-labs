# Name of the executable
TARGET = temp_display

# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2 -I/usr/include/freetype2


# Libraries to link
LIBS = -lX11 -lXft

# Source files
SRC = main.c

# Build rule
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Clean rule
clean:
	rm -f $(TARGET)
