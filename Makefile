CFLAGS=-g -O2
LIBS=-lGL -lGLU -lglut -lSOIL

all: src/main.cpp drawboard.o
	-@mkdir build
	g++ $(CFLAGS) src/main.cpp src/*.o $(LIBS) -o build/labyrinth.out

drawboard.o : src/drawboard.c
	g++ -c $(CFLAGS) src/drawboard.c $(LIBS) -o src/drawboard.o

clean:
	-@rm -f src/*.o
	-@rm -rf build
