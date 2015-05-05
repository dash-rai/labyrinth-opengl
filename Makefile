CFLAGS=-g -O2
LIBS=-lGL -lGLU -lglut -lSOIL -lBox2D

all: src/main.cpp drawboard.o startscreen.o
	-@mkdir build
	g++ $(CFLAGS) src/main.cpp src/*.o $(LIBS) -o build/labyrinth.out

drawboard.o : src/drawboard.c
	g++ -c $(CFLAGS) src/drawboard.c $(LIBS) -o src/drawboard.o

startscreen.o : src/startscreen.cpp
	g++ -c $(CFLAGS) src/startscreen.cpp $(LIBS) -o src/startscreen.o

clean:
	-@rm -f src/*.o
	-@rm -rf build
