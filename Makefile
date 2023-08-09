# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Name of the executable
TARGET = my_program

# Source file and object file
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

# Default rule, builds the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule to compile each source file into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJ) $(TARGET)
