RD = "../res/"

all:
	g++ -c -Wall -fPIC Randomizer.cpp -o $(RD)Randomizer.o
	g++ -shared -o $(RD)libRandomizer.so $(RD)Randomizer.o 

clean:
	rm $(RD)*.o $(RD)*.so