CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra
TARGET = pbl
SRC = src/main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

clean:
	rm -f $(TARGET)