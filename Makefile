CXX = g++
CXXFLAGS = -g -Wall -pedantic -Iinclude -std=c++17 -O2
EXECUTABLE = ttg
INC = ./src/include/
OBJECTS = main.o Args.o Generator.o
SRC = $(shell find $(INC) -type f -name '*.cpp')

all:	compile run

compile: $(OBJECTS) 
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

run:
	./$(EXECUTABLE)

clean:
	rm $(EXECUTABLE) $(OBJECTS)

main.o: ./src/main.cpp
	$(CXX) $(CXXFLAGS) -c ./src/main.cpp

%: %.o
	$(CXX) $(CXXFLAGS) -o $@ $*.o

%.o: $(INC)%.cpp $(INC)%.hpp
	$(CXX) $(CXXFLAGS) -c $(INC)$*.cpp
