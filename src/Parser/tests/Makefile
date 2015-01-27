CXX         = clang++
PARSER_DIR  = ..
BIN         = test_tokenizer.out test_parser.out
CCFLAGS     = -O2 

all: $(BIN)

test_tokenizer.out: test_tokenizer.cpp $(PARSER_DIR)/Tokenizer.cpp
	$(CXX) $(CCFLAGS) -o $@ $^

test_parser.out: test_parser.cpp $(PARSER_DIR)/Tokenizer.cpp $(PARSER_DIR)/Parser.cpp
	$(CXX) $(CCFLAGS) -o $@ $^

clean:
	-rm -f *.out *.o
