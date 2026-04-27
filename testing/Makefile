BD = $(realpath ../bin)
RD = $(realpath ../res)
TS = $(realpath ../testing)

all: cpp_version c_version

cpp_version:
	g++ -g -c -Wall -std=c++17 $(TS)/RandomizerExample.cpp
	mv *.o $(BD)
	g++ $(BD)/RandomizerExample.o -L$(RD) -lRandomizer -Wl,-rpath,$(RD)	\
							-o $(BD)/randomizer_cpp

c_version:
	gcc -g -c -Wall -std=c17 $(TS)/RandomizerCExample.c
	mv *.o $(BD)
	gcc $(BD)/RandomizerCExample.o -L$(RD) -lRandomizer -Wl,-rpath,$(RD)	\
							-o $(BD)/randomizer_c

clean:
	rm $(BD)/randomizer* *.o $(BD)/*.gch
