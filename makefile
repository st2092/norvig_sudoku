MAIN = main.cc
OBJECTS = possible_values.o sudoku.o
OUT = sudoku_solver

# compile components:
CXX = g++
FLAGS = -W -Wall -pedantic -ansi -Wextra -std=c++0x
CXXFLAG = -g $(FLAGS)
COMPFLAGS = -c $(FLAGS)

# basic compile commands:
COMPILE = $(CXX) $(CXXFLAGS)
COMPILE_ONLY = $(CXX) $(COMPFLAGS)

# compile
all: $(OBJECTS)
	$(COMPILE) $(MAIN) $(OBJECTS) -o $(OUT)

possible_values.o: possible_values.h possible_values.cc
	$(COMPILE_ONLY) possible_values.cc

sudoku.o: sudoku.h sudoku.cc
	$(COMPILE_ONLY) sudoku.cc

clean:
	rm -rf *.exe *.o *~ $(OUT)
