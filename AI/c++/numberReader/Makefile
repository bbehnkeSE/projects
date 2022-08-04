all: compile link clean run

compile:
	g++ -I include -c src/main.cpp src/display.cpp

link:
	g++ main.o display.o -o numberReader -Llib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o

run:
	./numberReader