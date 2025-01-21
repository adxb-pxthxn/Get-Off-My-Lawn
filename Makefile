#compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -I/opt/homebrew/Cellar/sfml/2.6.1/include
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

#target executable
TARGET = main

# Source and object files
SRC = main.cpp Game.cpp Character.cpp Money.cpp Peashooter.cpp Plant.cpp RedZombie.cpp Walnut.cpp Zombie.cpp
OBJ = $(SRC:.cpp=.o)

# Default rule
all: $(TARGET)

#link the target executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(TARGET)

#compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#clean up
clean:
	rm -f $(OBJ) $(TARGET)

#phony targets
.PHONY: all clean