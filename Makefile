#Current make system
IDIR=include/
SRC=src/
BIN=bin/
TEST=tests/

CXX=g++
CFLAGS= -O1 -std=c++17 -I$(IDIR)
LIBS= -lm



test: nnue_test
nnue_test:
	$(CXX) $(CFLAGS) $(TEST)layer_test.cpp -o $(BIN)$@ $(SRC)layers/*.cpp /usr/include/catch2/catch_amalgamated.cpp

#$(patsubst %,$(ODIR)/%,$(_OBJ))
#
#main: 
#bin/linear.o bin/relu.o
#	$(info $@)
#
#layers: 
#	$(CXX) $(CFLAGS) -c $(SRC)layers/linear.cpp -o $(BIN)linear.o
#	$(CXX) $(CFLAGS) -c $(SRC)layers/relu.cpp -o $(BIN)relu.o

#$test: 
#$	$(CXX) $(CFLAGS) -c $(TEST)layer_test.cpp -o $(BIN)test.o
	
