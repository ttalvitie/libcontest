SRC := $(wildcard *.cpp */*.cpp */*/*.cpp */*/*/*.cpp */*/*/*/*.cpp)
TEST := $(SRC:.cpp=.test)

all: $(TEST)

%.test: %.cpp
	g++ $< -o $@ -I../src/ -I. -Wall -O2 -g -MMD -Wno-sign-compare -std=c++0x

clean:
	rm $(TEST)

-include $(TEST:.test=.d) 
