CFLAGS=-g -O2 $(pkg-config --cflags bullet)
LIBS=-lGL -lGLU -lglut $(pkg-config --libs bullet)

all: src/main.cpp drawboard.o
	g++ $(CFLAGS) src/main.cpp src/*.o $(LIBS)
	-mkdir build
	mv a.out build/labyrinth

drawboard.o : src/drawboard.c
	g++ -c $(CFLAGS) src/drawboard.c $(LIBS)
	mv drawboard.o src/drawboard.o

clean:
	-rm -f src/*.o
	-rm -f build/*
	-rmdir build
