RD = $(realpath ../res)
SD = $(realpath ../src)

SRC_FILES = Randomizer.cpp
SRC_PATHS = $(addprefix $(SD)/,$(SRC_FILES))

OBJ_FILES = $(patsubst %.cpp,%.o, $(SRC_FILES))
OBJ_PATHS = $(addprefix $(RD)/,$(OBJ_FILES))

all:
	g++ -c -Wall -fPIC -std=c++17 $(SRC_PATHS)
	mv *.o $(RD)
	g++ -shared -o $(RD)/libRandomizer.so $(OBJ_PATHS)	

clean:
	rm $(RD)/*.o $(RD)/*.so