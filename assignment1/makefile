# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Files
TARGET = voronoi
SOURCES = main.cpp clusters.cpp nodes.cpp tabulist.cpp voronoi.cpp
HEADERS = clusters.h nodes.h tabulist.h voronoi.h
OBJECTS = $(SOURCES:.cpp=.o)

# Build Rules
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJECTS)
		$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source files into object files
%.o: %.cpp $(HEADERS)
		$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
		rm -f $(OBJECTS) $(TARGET)

