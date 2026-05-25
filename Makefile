CXX = clang++

RAYLIB_PATH = /opt/homebrew/opt/raylib

CXXFLAGS = -Wall -Wextra -std=c++17 \
            -Iinclude \
            -I$(RAYLIB_PATH)/include


LDFLAGS = -L$(RAYLIB_PATH)/lib -lraylib \
		   -framework CoreVideo \
		   -framework IOKit \
		   -framework Cocoa \
		   -framework GLUT \
		   -framework OpenGL

SRC = $(wildcard src/*.cpp)

OUT = main

all:
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
