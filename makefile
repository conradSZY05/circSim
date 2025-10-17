# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -g -Wall -std=c++17 -I. -Icomponents

# SFML libraries (optional, remove if not using SFML)
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files: all .cpp files in main folder + components folder
SRCS = $(wildcard *.cpp) $(wildcard components/*.cpp)

# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Output binary
TARGET = app

# Default target
all: $(TARGET)

# Link object files into final binary
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Compile each .cpp file into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)
