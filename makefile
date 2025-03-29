CC = g++
CCFLAGS = -std=c++11 -Wall -Wextra

SOURCES = test.cpp algoritmo.cpp memcount.cpp funcAux.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CCFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) parametros.txt

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all run clean