CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.
SRCS = main.cpp src/map.cpp src/player.cpp src/enemy.cpp src/items.cpp src/game.cpp src/audio.cpp

ifeq ($(OS),Windows_NT)
    TARGET = game.exe
    LDFLAGS =
else
    TARGET = game
    LDFLAGS = -lpthread -lm
endif

all: $(TARGET)
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS) $(LDFLAGS)
clean:
	rm -f $(TARGET)
.PHONY: all clean
