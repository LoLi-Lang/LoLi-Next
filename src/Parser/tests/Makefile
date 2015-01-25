CXX=clang++
PARSER_DIR=..
BIN=test_tokenizer.out

all: $(BIN)

test_tokenizer.out: test_tokenizer.cpp $(PARSER_DIR)/Tokenizer.cpp
	$(CXX) -o $@ $^

clean:
	-rm -f *.out *.o
