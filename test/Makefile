SRC := $(wildcard *.cpp */*.cpp */*/*.cpp */*/*/*.cpp */*/*/*/*.cpp)
TEST := $(SRC:.cpp=.test)

all: $(TEST)

%.test: %.cpp
	g++ $< -o $@ -I../src/ -Wall -g -MMD

-include $(TEST:.test=.d) 
