# Variables
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra
TARGET = pbl
SRC = src/main.cpp

# Default rule: builds the pbl binary
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Your custom pbuild command
# This compiles the code AND runs the list command immediately
pbuild: $(TARGET)
	./$(TARGET) list

# Clean rule: removes the binary so you can re-compile fresh
clean:
	rm -f $(TARGET)

# Install rule: moves it to your local bin (optional since you use aliases)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/