CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
TARGET   = amor_game

SRCS = main.cpp \
       src/map.cpp \
       src/player.cpp \
       src/enemy.cpp \
       src/items.cpp \
       src/input.cpp \
       src/renderer.cpp \
       src/game.cpp \
       src/audio.cpp \
       src/narrative.cpp

OBJS = $(SRCS:.cpp=.o)

ifeq ($(OS),Windows_NT)
    LDFLAGS =
else
    LDFLAGS = -lpthread -lm
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
