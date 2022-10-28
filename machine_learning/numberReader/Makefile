all: compile link clean

compile:
	g++ -I include -c src/test.cpp

link:
	g++ test.o -o test -Llib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o