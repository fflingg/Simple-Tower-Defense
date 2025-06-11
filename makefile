# Makefile: 编译 test.cpp，运行 main.out，然后清理中间文件

CXX = g++
CXXFLAGS = -I SFML-3.0.0/include -MMD -MP
LDFLAGS = -L SFML-3.0.0/lib -lsfml-graphics -lsfml-window -lsfml-system

SRC = test.cpp
OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)
TARGET = main.out

.PHONY: all clean

all: $(TARGET)
	@echo "✅ Running $(TARGET)..."
	./$(TARGET)
	@$(MAKE) clean

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	@echo "🧹 Cleaning up..."
	rm -f $(OBJ) $(DEP)

-include $(DEP)
