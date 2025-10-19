BD = "../bin/"
RD = "../res/"

all: cpp_version c_version

cpp_version:
	g++ -g -c -Wall -std=c++17 RandomizerExample.cpp
	g++ RandomizerExample.o -L$(RD) -lRandomizer -Wl,-rpath,$(RD)	\
							-o $(BD)randomizer_cpp

c_version:
	gcc -g -c -Wall -std=c17 RandomizerCExample.c
	gcc RandomizerCExample.o -L$(RD) -lRandomizer -Wl,-rpath,$(RD)	\
							-o $(BD)randomizer_c

clean:
	rm $(BD)randomizer* *.o $(BD)*.gch
