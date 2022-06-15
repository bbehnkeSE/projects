all: compile link clean run

compile:
	g++ -Iinclude -c src/main.cpp src/box.cpp

link:
	g++ main.o box.o -o bin/mazeRunner -Llib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o

run:
	./bin/mazeRunner