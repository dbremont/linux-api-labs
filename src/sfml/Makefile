# File: Makefile

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# SFML libraries to link
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Target executable name
TARGET = app

# Source files
SRC = main.cpp

# Build target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Clean build artifacts
clean:
	rm -f $(TARGET)
