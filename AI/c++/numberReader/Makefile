all: compile link clean

compile:
	g++ -I include -c src/generateTrainingData.cpp src/display.cpp

link:
	g++ generateTrainingData.o display.o -o generateTrainingData -Llib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o