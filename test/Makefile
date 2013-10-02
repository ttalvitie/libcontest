SRC := $(wildcard *.cpp */*.cpp */*/*.cpp */*/*/*.cpp */*/*/*/*.cpp)
TEST := $(SRC:.cpp=.test)

all: $(TEST)

%.test: %.cpp
	g++ $< -o $@ -I../src/ -Wall -O2 -g -MMD -Wno-sign-compare

clean:
	rm $(TEST)

-include $(TEST:.test=.d) 
