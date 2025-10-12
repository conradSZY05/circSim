# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -g -Wall -std=c++17 -Iinclude

# SFML libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files (all .cpp files inside src/)
SRCS = $(wildcard src/*.cpp)

# Object files (mirror src/ -> build/)
OBJS = $(SRCS:.cpp=.o)

# Output binary
TARGET = app

# Default target: build everything
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Compile .cpp files into .o files
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)