RD = "../res/"
BD = "../bin/"

all: compile link

compile:
	g++ -g -c -std=c++17 Main.cpp

link: 
	g++ Main.o -L$(RD) -lRandomizer -Wl,-rpath,$(RD) -o $(BD)randomizer

clean:
	rm $(BD)randomizer $(BD)*.o $(BD)../bin/*.gch
