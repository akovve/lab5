CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = lab5_oop

SRCS = main.cpp task1.cpp task2.cpp task3.cpp task4.cpp task5.cpp task6.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = task.h task1.h task2.h task3.h task4.h task5.h task6.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) *.bin *.txt

run: $(TARGET)
	./$(TARGET)

help:
	@echo "Доступные команды:"
	@echo "  make all    - собрать программу"
	@echo "  make clean  - удалить скомпилированные файлы"
	@echo "  make run    - собрать и запустить программу"
	@echo "  make help   - показать эту справку"

.PHONY: all clean run help