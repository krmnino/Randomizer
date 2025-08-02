all: compile link

compile:
	g++ -g -c -std=c++17 Main.cpp ../src/Randomizer.hpp

link: 
	g++ -o randomizer Main.o

clean:
	rm randomizer *.o ../src/*.gch
