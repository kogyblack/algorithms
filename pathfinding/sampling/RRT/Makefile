# C++ Compiler
CXX=clang++
CXXFLAGS=-c -g -Wall -std=c++11
LDFLAGS = $(addprefix -l,$(LIBS))

SOURCES := $(wildcard *.cpp)

OBJECTS := $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE = rrt.out

.PHONY: clean obj

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ $(LDFLAGS) -o $@

$(OBJECTS): | obj

obj:
	mkdir -p $@

obj/%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -o $@

clean:
	- $(RM) -R obj $(EXECUTABLE)

rebuild:
	make clean
	make
