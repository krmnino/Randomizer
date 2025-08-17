BD = "../bin/"
SD = "../src/"

SRC_FILES = $(SD)Randomizer.cpp	\
	        Main.cpp

OBJ_FILES = Randomizer.o		\
	        Main.cpp

all: compile link

compile:
	g++ -g -c -std=c++17 $(SRC_FILES)

link: 
	g++ $(OBJ_FILES) -o $(BD)randomizer

clean:
	rm $(BD)randomizer *.o $(BD)*.gch
