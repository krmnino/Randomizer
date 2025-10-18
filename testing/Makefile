BD = "../bin/"
SD = "../src/"

SRC_FILES = $(SD)Randomizer.cpp	\
	        RandomizerExample.cpp

OBJ_FILES = Randomizer.o		\
	        RandomizerExample.o

all: compile link

compile:
	g++ -g -c -Wall -std=c++17 $(SRC_FILES)

link: 
	g++ $(OBJ_FILES) -o $(BD)randomizer

clean:
	rm $(BD)randomizer *.o $(BD)*.gch
