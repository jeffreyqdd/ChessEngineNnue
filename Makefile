#Current make system
IDIR=include
SRC=src
BIN=bin
TEST=tests

CXX=g++
CFLAGS=-O2 -g -std=c++20 -I$(IDIR)/
LIBS=-lm -lfmt

## BUILD RULES 
$(BIN)/%.o: $(SRC)/%.cpp $(IDIR)/%.hpp 
	$(CXX) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: $(SRC)/layers/%.cpp $(IDIR)/%.hpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: $(TEST)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

### LINKING (generates executables)
$(BIN)/nnue_test : $(BIN)/layer_test.o $(BIN)/catch_amalgamated.o $(BIN)/linear.o
	$(CXX) $(CFLAGS) -o $@ $^ $(LIBS)

test: $(BIN)/nnue_test

.PHONY: clean

clean:
	rm $(BIN)/* 
