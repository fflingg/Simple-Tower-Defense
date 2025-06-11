# Compiler and flags
CXX = g++
CXXFLAGS = -I SFML-3.0.0/include
LDFLAGS = -L SFML-3.0.0/lib
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Targets
TARGET = main.out
SRC = test.cpp

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean