CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++11

SRC = src/SerialPort.cpp src/SerialManager.cpp src/main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = send_messages

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
