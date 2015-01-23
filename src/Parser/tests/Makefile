CXX=clang++
PARSER_DIR=..

all: token_test.out

token_test.out: test_tokenizer.cpp $(PARSER_DIR)/Tokenizer.cpp
	$(CXX) -o $@ $^

